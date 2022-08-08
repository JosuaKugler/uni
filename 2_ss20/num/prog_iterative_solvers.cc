#include <iostream>    // notwendig zur Ausgabe
#include <vector>
#include "../hdnum/hdnum.hh"    // hdnum header
#include <chrono>

namespace hdnum {

  template<typename REAL>
  class SparseMatrix {

    struct MatrixEntry {
      int i;
      int j;
      REAL value;
    };

  public:
    SparseMatrix( DenseMatrix<REAL>& A) {
      for (size_t i = 0; i < A.rowsize(); i++)
      {
        for (size_t j = 0; j < A.colsize(); j++)
        {
          AddEntry(i, j, A[i][j]);
        } 
      }
    }

    void AddEntry (int i, int j, REAL value) {
      assert(i >= 0);
      assert(j >= 0);
      if (value != .0)
        entries.push_back(MatrixEntry{.i=i, .j=j, .value=value});
    }

    template<typename V>
    void mv (Vector<V>& y,  Vector<V>& x) {

      zero(y);

      for (MatrixEntry& matrix_entry : entries) {
        assert(y.size() > matrix_entry.i);
        assert(x.size() > matrix_entry.j);
        y[matrix_entry.i] += matrix_entry.value * x[matrix_entry.j];
      }
    }

  private:
    std::vector<MatrixEntry> entries;
  };

  void invert_ltr(hdnum::DenseMatrix<double>& A, hdnum::DenseMatrix<double>& W_i, int n){
   for(int i = 0; i<n; ++i){
      for(int j = 0; j <= i; ++j){ //Elemente über der Hauptidag. sind 0
        if(j==i){
          // Wegen W, W^{-1} untere Dreiecksmatrix 
          W_i[i][j] = 1./A[i][j];
        }else{
          // Wir haben insg., dass (L+D)*W^{-1} = I nach Konstr. 
          // Wir bauen W_i schritweise auf und wir konstruieren hier das Element W_i[i][j]. Alle Zeilen darüber
          // wurden bereits konstruiert. 
          // Wenn wir die i-te Zeile von A mit der j-ten Spalte von W_i mult. kommen folgende Fälle auf
          // 1. Für k > i ist A[i][k] = 0   2. Für m < j ist W_i[m][j] = 0
          // D.h. wir erhalten insg., dass nur für die Indizes j <= j < i-1 beie Faktoren != 0 sind. 
          // Wir wollen, dass es insg. Null ergibt => bilden also das "Skalarprodukt" und teilen durch -1./A[i][i]
          for(int k = j; k < i-1; ++k){
            W_i[i][j] -= A[i][k]*W_i[j][k];
          }
          // und wir teilen durch das HD-Element
          W_i[i][j] *= 1./A[i][i];
        }
      }
    }
  }
}


void r_iteration( hdnum::DenseMatrix<double>& A, hdnum::Vector<double>& x,  hdnum::Vector<double>& b, double epsilon, double omega) {
  int N = A.colsize();
  hdnum::Vector<double> ax(N);
  A.mv(ax,x);
  hdnum::Vector<double> d = b - ax;
  double zieldefekt = epsilon * d.two_norm();
  int counter(0);
  while (d.two_norm() > zieldefekt) //defektnorm > epsilon * anfangsdefekt
  {
    for (int i = 0; i < N; i++)
    {
      x[i] += omega * d[i];
    }
    A.mv(ax,x);
    d = b - ax;
    ++counter;
  }
  //std::cout << counter << " Iterationen" << std::endl;
}

void r_iteration_sparse(hdnum::SparseMatrix<double>& A, int N, hdnum::Vector<double>& x,  hdnum::Vector<double>& b, double epsilon, double omega) {
  hdnum::Vector<double> ax(N);
  A.mv(ax,x);
  hdnum::Vector<double> d = b - ax;
  double zieldefekt = epsilon * d.two_norm();
  int counter(0);
  while (d.two_norm() > zieldefekt) //defektnorm > epsilon * anfangsdefekt
  {
    for (int i = 0; i < N; i++)
    {
      x[i] += omega * d[i];
    }
    A.mv(ax,x);
    d = b - ax;
    ++counter;
  }
  //std::cout << counter << " Iterationen" << std::endl;
}

void jac_iteration( hdnum::DenseMatrix<double>& A, hdnum::Vector<double>& x,  hdnum::Vector<double>& b, double epsilon) {
  int N = A.colsize();
  hdnum::Vector<double> ax(N);
  hdnum::Vector<double> w(N);
  for (size_t i = 0; i < A.colsize(); i++)
  {
    w[i] = 1/A[i][i];
  }
  A.mv(ax,x);
  hdnum::Vector<double> d = b - ax;
  double zieldefekt = epsilon * d.two_norm();
  int counter(0);
  while (d.two_norm() > zieldefekt) //defektnorm > epsilon * anfangsdefekt
  {
    x = w * d;
    A.mv(ax,x);
    d = b - ax;
    ++counter;
  }
  //std::cout << counter << " Iterationen" << std::endl;
}

void jac_iteration_sparse( hdnum::DenseMatrix<double>& A, hdnum::SparseMatrix<double>& A_sparse, hdnum::Vector<double>& x,  hdnum::Vector<double>& b, double epsilon) {
  int N = A.colsize();
  hdnum::Vector<double> ax(N);
  hdnum::Vector<double> w(N);
  for (size_t i = 0; i < A.colsize(); i++)
  {
    w[i] = 1/A[i][i];
  }
  A_sparse.mv(ax,x);
  hdnum::Vector<double> d = b - ax;
  double zieldefekt = epsilon * d.two_norm();
  int counter(0);
  while (d.two_norm() > zieldefekt) //defektnorm > epsilon * anfangsdefekt
  {
    for (int i = 0; i < N; i++)
    {
      x[i] += w[i] * d[i];
    }
    A_sparse.mv(ax,x);
    d = b - ax;
    ++counter;
  }
  //std::cout << counter << " Iterationen" << std::endl;
}

void gs_iteration( hdnum::DenseMatrix<double>& A, hdnum::Vector<double>& x,  hdnum::Vector<double>& b, double epsilon) {
  int N = A.colsize();
  hdnum::Vector<double> ax(N);
  A.mv(ax,x);
  hdnum::Vector<double> d = b - ax;
  double zieldefekt = epsilon * d.two_norm();
  int counter(0);
  while (d.two_norm() > zieldefekt) //defektnorm > epsilon * anfangsdefekt
  {
    //update x (x += W_inverse * d), ax wird hier als temporärer speichervektor benutzt
    for (int i = 0; i < N; i++)
    {
      ax[i] = d[i];
      for (int j = 0; j < i; j++)
      {
        ax[i] -= A[i][j] * ax[j];
      }
      ax[i] /= A[i][i];
    }
    x += ax;
    A.mv(ax,x);
    d = b - ax;
    ++counter;
  }
  //std::cout << counter << " Iterationen" << std::endl;
}

void gs_iteration_with_w(hdnum::DenseMatrix<double>& A, hdnum::SparseMatrix<double> A_sparse, hdnum::Vector<double>& x,  hdnum::Vector<double>& b, double epsilon) {
  int N = A.colsize();
  hdnum::Vector<double> ax(N);
  A_sparse.mv(ax,x);
  hdnum::DenseMatrix<double> W_i(N,N,0);
  hdnum::invert_ltr(A, W_i, N);
  hdnum::SparseMatrix<double> W(W_i);
  hdnum::Vector<double> d = b - ax;
  double zieldefekt = epsilon * d.two_norm();
  int counter(0);
  while (d.two_norm() > zieldefekt) //defektnorm > epsilon * anfangsdefekt
  {
    //update x (x += W_inverse * d), ax wird hier als temporärer speichervektor benutzt
    W.mv(ax, d);
    x += ax;
    A_sparse.mv(ax,x);
    d = b - ax;
    ++counter;
  }
  //std::cout << counter << " Iterationen" << std::endl;
}


void gs_iteration_sparse( hdnum::DenseMatrix<double>& A, hdnum::SparseMatrix<double> A_sparse, hdnum::Vector<double>& x,  hdnum::Vector<double>& b, double epsilon) {
  int N = A.colsize();
  hdnum::Vector<double> ax(N);
  A_sparse.mv(ax,x);
  hdnum::Vector<double> d = b - ax;
  double zieldefekt = epsilon * d.two_norm();
  int counter(0);
  int bandweite = 0;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (A[i][j] != 0)
      {
        if (i-j > bandweite)
        {
          bandweite = i-j;
        }
      }
    }
  }
  while (d.two_norm() > zieldefekt) //defektnorm > epsilon * anfangsdefekt
  {
    //update x (x += W_inverse * d), ax wird hier als temporärer speichervektor benutzt
    for (int i = 0; i < N; i++)
    {
      ax[i] = d[i];
      for (int j = i-bandweite; j < i; j++)
      {
        ax[i] -= A[i][j] * ax[j];
      }
      ax[i] /= A[i][i];
    }
    x += ax;
    A_sparse.mv(ax,x);
    d = b - ax;
    ++counter;
  }
  //std::cout << counter << " Iterationen" << std::endl;
}

auto R_duration( hdnum::DenseMatrix<double>& A, hdnum::Vector<double>& b, hdnum::Vector<double>& x, double epsilon, double omega, bool sparse) {
  auto t1 = std::chrono::high_resolution_clock::now();
  if (sparse) {
    hdnum::SparseMatrix<double> A_sparse(A);
    r_iteration_sparse(A_sparse, A.colsize(), x, b, epsilon, omega);
  }
  else
    r_iteration(A, x, b, epsilon, omega);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  return duration;
}

auto Jac_duration( hdnum::DenseMatrix<double>& A, hdnum::Vector<double>& b, hdnum::Vector<double>& x, double epsilon, bool sparse) {
  auto t1 = std::chrono::high_resolution_clock::now();
  if (sparse) {
    hdnum::SparseMatrix<double> A_sparse(A);
    jac_iteration_sparse(A, A_sparse, x, b, epsilon);
  }
  else
    jac_iteration(A, x, b, epsilon);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  return duration;
}

auto GS_duration( hdnum::DenseMatrix<double>& A, hdnum::Vector<double>& b, hdnum::Vector<double>& x, double epsilon, bool sparse) {
  auto t1 = std::chrono::high_resolution_clock::now();
  if (sparse) {
    hdnum::SparseMatrix<double> A_sparse(A);
    gs_iteration_sparse(A, A_sparse, x, b, epsilon);
    //gs_iteration_with_w(A, A_sparse, x, b, epsilon); //even slower
  }
  else
    gs_iteration(A, x, b, epsilon);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  return duration;
}

auto LU_duration(hdnum::DenseMatrix<double>& A, hdnum::Vector<double>& x, hdnum::Vector<double>& b) {
  auto t1 = std::chrono::high_resolution_clock::now();
  hdnum::linsolve(A,x,b);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  return duration;
}

int main ()
{
  for (int n = 4; n < 10; n++)
  {
    int N = 1 << n; //N = 2^n

    // Testmatrix aufsetzen
    hdnum::DenseMatrix<double> A(N,N,.0);
    for (typename hdnum::DenseMatrix<double>::size_type i=0; i<A.rowsize(); ++i)
    {
      if (i > 0) {
        A[i][i-1] = 1.0;
      }
      if (i + 1 < A.colsize()) {
        A[i][i+1] = 1.0;
      }
      A[i][i] -= 2.0;
    }

    // Rechte Seite und Lösungsvektor
    hdnum::Vector<double> x(N, 0.0);
    hdnum::Vector<double> b(N, 1.0);

    // Lösen Sie nun A*x=b iterativ
    double epsilon = 0.0001;
    double omega = -0.5; //for richardson iteration
    bool sparse = true;

    auto r_duration = R_duration(A, b, x, epsilon, omega, sparse);
    std::cout << "Richardson-Iteration Laufzeit: " << r_duration << ", Abweichung: " << (A * x - b).two_norm()<< std::endl;
    zero(x);
    auto jac_duration = Jac_duration(A, b, x, epsilon, sparse);
    std::cout << "Jacobi-Iteration Laufzeit: " << jac_duration << ", Abweichung: " << (A * x - b).two_norm()<< std::endl;
    zero(x);
    auto gs_duration = GS_duration(A, b, x, epsilon, sparse);
    std::cout << "Gauss-Seidel-Iteration Laufzeit: " << gs_duration << ", Abweichung: " << (A * x - b).two_norm() << std::endl;
    zero(x);
    auto lu_duration = LU_duration(A, x, b);
    std::cout << "LU-Zerlegung Laufzeit: " << lu_duration << std::endl;
    //std::cout << n << "," << r_duration << "," << jac_duration << "," << gs_duration << "," << lu_duration << std::endl;
  }
}