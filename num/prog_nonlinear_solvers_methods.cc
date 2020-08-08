#include <iostream>
#include <vector>
#include "../hdnum/hdnum.hh"

template<class N>
class EllipseProblem
{
public:
  // Exportiere Größentyp
  typedef std::size_t size_type;

  // Exportiere Zahlentyp
  typedef N number_type;

  // Dimension der untenstehenden Funktion
  std::size_t size () const
  {
    return 2;
  }

  // Funktionsauswertung
  void F (const hdnum::Vector<N>& x, hdnum::Vector<N>& result) const
  {
    result[0] = x[0]*x[0] + x[1]*x[1] - 4;
    result[1] = x[0]*x[0]/9 + x[1]*x[1] - 1;
  }

  // Jacobimatrix
  void F_x (const hdnum::Vector<N>& x, hdnum::DenseMatrix<N>& result) const
  {
    result[0][0] = 2*x[0];    result[0][1] = 2*x[1];
    result[1][0] = 2*x[0]/9;  result[1][1] = 2*x[1];
  }
};

int main ()
{
  typedef double Number; // Zahlentyp


  typedef EllipseProblem<Number> Problem;
  Problem problem;


  hdnum::Vector<Number> u(problem.size()); // Vektor für Startpunkt bzw Lösung

  // Newton
  hdnum::Newton newton;
  newton.set_maxit(20);
  newton.set_verbosity(2);
  newton.set_reduction(1e-10);
  newton.set_abslimit(1e-20);
  newton.set_linesearchsteps(3);


  u[0] = -2.0; u[1] = -1.0; // Startwert
  newton.solve(problem,u);
  std::cout << "Ergebnis: " <<  std::setprecision(15) << u << std::endl;
  hdnum::Vector<Number> result(problem.size());
  problem.F(u, result);
  std::cout << "f(Ergebnis): " << result << std::endl;


   // Relaxation
  hdnum::Banach banach;
  banach.set_maxit(5000);                  // set parameters
  banach.set_verbosity(2);
  banach.set_reduction(1e-6);
  banach.set_abslimit(1e-20);
  banach.set_sigma(-0.01);

  u[0] = 1.5; u[1] = 0.8; // Startwert
  banach.solve(problem,u);

  std::cout << "Ergebnis: " <<  std::setprecision(15) << u << std::endl;
  problem.F(u, result);
  std::cout << "f(Ergebnis): " << result << std::endl;
  return 0;
}
