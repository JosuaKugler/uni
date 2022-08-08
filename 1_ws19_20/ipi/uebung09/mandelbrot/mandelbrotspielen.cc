#include <iostream>
#include <cmath>
#include <string>
#include "/home/josua/uni/ipi/ipiclib/fcpp.hh"

// Datentyp Complex in der Datei canvas.hh
#include "canvasspielen.hh"

typedef long double my_double;

// Summiert zwei komplexe Zahlen z und c und schreibt das Ergebnis in z
void add_complex(Complex& z, Complex c)
{
  //std::cout << "(" << z.real << "+i*" << z.imag << ") + (" << c.real << "+i*" << c.imag << ")";
  z.real = z.real + c.real;
  z.imag = z.imag + c.imag;
  //std::cout << "= (" << z.real << "+i*" << z.imag << ")" << std::endl; 
}
// Multipliziert zwei komplexe Zahlen z und c und schreibt das Ergebnis in z
void multiply_complex(Complex& z, Complex c)
{
  //std::cout << "(" << z.real << "+i*" << z.imag << ") * (" << c.real << "+i*" << c.imag << ")";
  my_double zimag = z.imag;
  my_double zreal = z.real;
  my_double cimag = c.imag;
  my_double creal = c.real;
  z.imag = (zimag * creal) + (zreal * cimag);
  z.real = (zreal * creal) - (zimag * cimag);
  //std::cout << "= (" << z.real << "+i*" << z.imag << ")" << std::endl;
}

// Betrag einer komplexen Zahl
my_double betrag(Complex z)
{
  // TODO Nutzen Sie std::sqrt zur Wurzelberechnung
  return std::sqrt(z.real*z.real + z.imag*z.imag);
}

int grauwert(Complex z, int maxIt, my_double threshold, Complex c)
{
  int Itnumber = 0;
  int It = 0;
  bool continuebool = true;
  while(It < maxIt and continuebool)
  {
    //std::cout << z.real << "+i*" << z.imag<< std::endl;
    ++It;
    multiply_complex(z,z);
    add_complex(z,c);
    if (betrag(z) > threshold)
    {
      continuebool = false;
      Itnumber = It;
    }
  }

  int grauwert_value;
  //betrag wurde nie größer als treshold
  if (continuebool)
  {
    grauwert_value = 0;
  }
  //betrag wurde nach Itnumber größer als treshold
  else
  {
    //std::cout << std::log(Itnumber * 100000) << std::endl;
    grauwert_value = (int) (std::log(Itnumber) * 100);
    //grauwert_value = 1;
  }
  //print(grauwert_value);
  return grauwert_value;
}


// TODO Funktion mandelbrot()
void julia(Canvas& canvas, my_double threshold,
int maxIt, std::string filename)
{
  for (int i = 0; i < canvas.vertPixels(); i++)
  {
    for (int j = 0; j < canvas.horPixels(); j++)
    {
      //std::cout << canvas.coord(i,j).real << std::endl;
      int grauwert_value = grauwert(canvas.coord(i,j), maxIt, threshold, canvas.get_c());
      canvas.writePixel(i, j , grauwert_value);
    }
  }
  canvas.write(filename);
}

int main(int argc, char** argv)
{
  my_double real = readarg_double(argc, argv, 1);
  my_double imag = readarg_double(argc, argv, 2);
  my_double zoom = readarg_double(argc, argv, 3);
  Complex c;
  c.real = real;
  c.imag = imag;
  //Canvas::Canvas(my_double center_x, my_double center_y,my_double width, my_double height,int horPixels, int vertPixels)
  Canvas juliacanvas(-1, 0, 1000, 1000, 4000, 3000, c, zoom);
  //mandelbrot(Canvas& canvas, my_double threshold, int maxIt, std::string filename)
  julia(juliacanvas, 100, 50, "mandelbrotbild");
  return 0;
}