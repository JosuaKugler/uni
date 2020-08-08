#include <iostream>
#include <vector>
#include "../hdnum/hdnum.hh"


template<class N>
class PolynomialProblem
{
public:
  // Exportiere Größentyp
  typedef std::size_t size_type;

  // Exportiere Zahlentyp
  typedef N number_type;

  // Dimension der untenstehenden Funktion
  std::size_t size () const
  {
    return 1;
  }

  // Funktionsauswertung
  void F (const hdnum::Vector<N>& x, hdnum::Vector<N>& result) const
  {
    result[0] = x[0]*x[0]*x[0]*x[0] + 4.0;
  }

  // Jacobimatrix
  void F_x (const hdnum::Vector<N>& x, hdnum::DenseMatrix<N>& result) const
  {
    result[0][0] = 4.0*x[0]*x[0]*x[0];
  }
};


int main ()
{
  typedef std::complex<double> Number; // Der Zahlentyp soll hier komplex sein

  typedef PolynomialProblem<Number> Problem;
  Problem problem;


  // Wir schauen Startpunkte auf einem Raster an, das später in ein Bild umgesetzt werden soll
  for (double start_value_i = -5.0; start_value_i <= 5.0; start_value_i += 1e-2) {

    for (double start_value = -5.0; start_value <= 5.0; start_value += 1e-2) {

      hdnum::Vector<Number> u(problem.size()); // Vektor für Startpunkt bzw Lösung
      u[0] = Number(start_value, start_value_i); // Startpunkt

      hdnum::Newton newton;
      newton.set_maxit(20);
      newton.set_verbosity(0);
      newton.set_reduction(1e-10);
      newton.set_abslimit(1e-20);
      newton.set_linesearchsteps(3);

      newton.solve(problem,u); // Lösen

      double id = 0;
      if(newton.has_converged()) {

        // Falls unser Newton-Löser konvertiert ist, stellen wir fest welche Nullstelle
        // Nullstelle wir getroffen haben und legen einen Index für jede Nullstelle fest.

        if (u[0].real() < 0)
          if (u[0].imag() < 0)
            id = 1;
          else if (u[0].imag() > 0)
            id = 2;
        else if (u[0].imag() < 0)
          id = 3;
        else if (u[0].imag() > 0)
          id = 4;
        else
          std::cout << "Unbekannte Nullstelle!" << std::endl;

        // Damit auch der "Abstand" zur Nullstelle (im Sinne von benötigten Iterationen
        // um sie zu erreichen) sichtbar wird, addieren wir noch die Iterationszahl
        // um einen Faktor abgeschwächt
        id += .1 * (double)newton.iterations();
      }

      std::cout << id << ",";
    }

    std::cout << std::endl;
  }

  return 0;
}
