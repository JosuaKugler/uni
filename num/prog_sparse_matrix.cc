#include <iostream>    // notwendig zur Ausgabe
#include <vector>
#include <random>
#include <chrono>
#include "../hdnum/hdnum.hh"    // hdnum header

namespace hdnum {

  template<typename REAL>
  class SparseMatrix {

    struct MatrixEntry {
      int i;
      int j;
      REAL value;
    };

  public: 

    void AddEntry (int i, int j, REAL value) {
      if (value != 0) {
        MatrixEntry newEntry = {i , j, value};
        entries.push_back(newEntry);
      };
    }

    template<typename V>
    void mv (Vector<V>& y, const Vector<V>& x) {
      for (auto & element : y) {
        element = 0;
      }
      for (MatrixEntry & entry : entries) {
        y[entry.i] += entry.value * x[entry.j];
      }
    }

  private:
    std::vector<MatrixEntry> entries;
  };
}

template<class NumberType>
void flussDenseMatrix( hdnum::DenseMatrix<NumberType> &A , int n)//n: Anzahl der Knoten
{
  int M( A.rowsize() );
  int N( A.colsize() );
  if(M!=N)
    HDNUM_ERROR("Matrix muss quadratisch sein!");

  // TODO Implementieren Sie hier das Aufstellen der Matrix des
  // Rohleitungsgleichungssystems
  hdnum::DenseMatrix<NumberType> B(2*n*(n-1), n*n - 1, 0); 

  int layer = -1; //anzahl der vertikalen rohre, 
  //die man durchlaufen muss, um zum aktuell betrachteten rohr zu kommen
  int startnode = 0; //von diesem knoten kommt das rohr
  int endnode = 0; //in diesen knoten muendet das rohr
  for (size_t edgeindex = 0; edgeindex < 2*n*(n-1); edgeindex++)
  {
    if (edgeindex < n*(n-1)) //horizontale rohre
    {
      if (edgeindex % (n-1) == 0) //pro schicht sind es immer n-1 rohre
        layer ++;
      startnode = edgeindex - 1 + layer;
      endnode = startnode + 1;
    }
    else //vertikale rohre
    {
      startnode = edgeindex - n*(n-1) -1;
      endnode = startnode + n;
    }
    //trage startnode und endnode in der matrix ein
    if (startnode >= 0) 
      B(edgeindex, startnode) = -1;
    B(edgeindex, endnode) = 1;
  }
  A = B.transpose() * B;
}

template<class REAL>
void DenseMatrix2SparseMatrix( hdnum::SparseMatrix<REAL>& A, hdnum::DenseMatrix<REAL>& B) {
  for (size_t i = 0; i < B.rowsize(); i++)
  {
    for (size_t j = 0; j < B.colsize(); j++)
    {
      REAL value = B[i][j];
      if (value != 0)
        A.AddEntry(i,j,B[i][j]);
    }
  }
}

void TestSparseMatrix(int N) {
  int n(N * N-1);
  hdnum::SparseMatrix<double> A;
  hdnum::DenseMatrix<double> B(n,n);
  hdnum::Vector<double> x(n,1);
  hdnum::Vector<double> y1(n,0);
  hdnum::Vector<double> y2(n,0);
  flussDenseMatrix(B, N);
  DenseMatrix2SparseMatrix(A,B);
  A.mv(y1,x);
  B.mv(y2,x);
  //std::cout << "Norm der Abweichung: " << (y2-y1).two_norm() << std::endl;
}

time_t SparseMultiplicationTime(hdnum::SparseMatrix<double> &A, int size) {
  hdnum::Vector<double> x(size, 1);
  hdnum::Vector<double> y(size);
  auto t1 = std::chrono::high_resolution_clock::now();
  A.mv(y,x);
  auto t2 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

  return duration;
  /* measures only seconds so not very useful
  time_t starttime;
  time_t endtime;
  time(&starttime);
  A.mv(y,x);
  time(&endtime);
  return endtime-starttime;
  */ 
}

time_t DenseMultiplicationTime(hdnum::DenseMatrix<double> &A, int size) {
  hdnum::Vector<double> x(size, 1);
  hdnum::Vector<double> y(size);
  auto t1 = std::chrono::high_resolution_clock::now();
  A.mv(y,x);
  auto t2 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

  return duration;
  /* measures only seconds so not very useful
  time_t starttime;
  time_t endtime;
  time(&starttime);
  A.mv(y,x);
  time(&endtime);
  return endtime-starttime;
  */ 
}

void BandMatrix(hdnum::SparseMatrix<double> &A, hdnum::DenseMatrix<double> &B, int size, int width, double max) {
  double lower_bound = -max;
  double upper_bound = max;
  std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
  std::default_random_engine re;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      if (abs(i - j) < width) {
        double value = unif(re);
        A.AddEntry(i, j, value);
        B[i][j] = value;
      };
    }
  }
}

void TimeBandMatrixMultiplication(int n) {
  int size = 1 << n; //2^n
  int width(100);
  double max(100);
  hdnum::SparseMatrix<double> A;
  hdnum::DenseMatrix<double> B(size, size);
  BandMatrix(A,B,size,width,max);
  if (n<4)
    std::cout << B << std::endl;
  time_t sparsetime = SparseMultiplicationTime(A, size);
  time_t densetime = DenseMultiplicationTime(B, size);
  std::cout << n << ", " << sparsetime << ", " << densetime << std::endl;
}

int main ()
{
  TestSparseMatrix(10);
  for (size_t i = 4; i < 15; i++)
  {
    TimeBandMatrixMultiplication(i);
  }
}
