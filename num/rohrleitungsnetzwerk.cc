// Kompilieren mit:
//
// g++ -I../hdnum/ -o rohrleitungsnetzwerk rohrleitungsnetzwerk.cc
//
// Das setzt voraus, dass ihr Programm in einem Ordner parallel zur
// entpackten HDNum Bibliothek liegt.

#include <iostream>
#include <cstdlib>
#include "hdnum.hh"


// Funktion zum Aufstellen der Matrix
template<class NumberType>
void flussMatrix( hdnum::DenseMatrix<NumberType> &A , int n)//n: Anzahl der Knoten
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


// Funktion zur Berechnung der Frobenius-Norm einer Matrix
template<class NumberType>
NumberType frobeniusNorm(const hdnum::DenseMatrix<NumberType> &A)
{
  // Error checking
  int M(A.rowsize());
  int N(A.colsize());
  if(M!=N)
    HDNUM_ERROR("Matrix muss quadratisch sein!");

  NumberType result=0.0;

  // TODO Implementieren Sie hier die Frobeniusnorm
  for (size_t i = 0; i < M; i++)
  {
    for (size_t j = 0; j < N; j++)
    {
      NumberType val = abs(A(i,j));
      result += val * val;
    }
  }
  result = sqrt(result);
  return result;
}


// Funktion zur Berechnung des betragsgrößten Eigenwertes mit Potenzmethode
template<class NumberType>
NumberType maxEigenwert(const hdnum::DenseMatrix<NumberType> &A)
{
  hdnum::DenseMatrix<NumberType> Anonconst = A;
  // Error checking
  int M(A.rowsize());
  int N(A.colsize());
  if(M!=N)
    HDNUM_ERROR("Matrix muss quadratisch sein!");

  // TODO Implementieren Sie hier die Potenzmethode
  hdnum::Vector<NumberType> rk(N,1.0);
  size_t max_it = 1000; //Anzahl der Iterationen

  for (size_t k = 0; k < max_it; k++)
  {
    rk = Anonconst * rk;
    rk /= rk.two_norm(); //r_k -> r_{k+1}
  }
  hdnum::Vector<NumberType> ark = Anonconst * rk;
  NumberType lambdak = (rk * ark) / rk.two_norm(); //\lambda_k wie auf dem Übungsblatt definiert
  rk *= lambdak;
  //std::cout << "Abweichung ||A * rk - lambdak * rk|| =" << (ark - rk).two_norm() << std::endl;
  return lambdak;
}

// Hauptprogramm
int main(int argc, char ** argv)
{

  // Anzahl der Knoten
  const int N(10);
  std::cout << "Knotenanzahl N: " << N << std::endl;

  // Größe der Matrix
  const int n(N*N-1);

  // Datentyp für die Matrix
  typedef double REAL;

  // Matrix initialisieren
  hdnum::DenseMatrix<REAL> A(n,n);

  // Pretty-printing einmal setzen für alle Matrizen
  A.scientific(false);
  A.width(15);

  flussMatrix(A, N);
  if (N<=4)
    std::cout << A << std::endl;

  // Bei Schwierigkeiten mit Teilaufgabe a) können Sie Teilaufgaben b)
  // und c) mit folgender Matrix testen
  int size_b = 4;
  hdnum::DenseMatrix<REAL> B(size_b,size_b);
  for (std::size_t i=0; i<size_b; ++i)
  {
    for (std::size_t j=0; j<size_b; ++j)
    {
      B[i][j] = i+j;
    }
  }

  // TODO Geben Sie hier alle verfügbaren Matrixnormen von A (bzw. B)
  // sowie den maximalen Eigenwert aus
  REAL norm_1 = A.norm_1();
  REAL norm_infty = A.norm_infty();
  REAL norm_f = frobeniusNorm(A);
  std::cout << "1-norm: " << norm_1;
  std::cout << ", unendlich-norm: " << norm_infty;
  std::cout << ", frobenius-norm: "<< norm_f;
  std::cout << ", maximaler Eigenwert: " << maxEigenwert(A) << std::endl;
  return 0;
}
//b) für N = 10 gibt das Programm folgendes aus: 1-norm: 8, unendlich-norm: 8, frobenius-norm: 41.1582
//c) der maximale Eigenwert für N = 10 ist näherungsweise 7.72136