#include <iostream>
#include <cmath>
#include <string>
#include "/home/josua/uni/ipi/ipiclib/fcpp.hh"

// Datentyp Complex in der Datei canvas.hh
#include "canvas.hh"

// Summiert zwei komplexe Zahlen z und c und schreibt das Ergebnis in z
void add_complex(Complex& z, Complex c)
{
  //std::cout << "(" << z.real << "+i*" << z.imag << ") + (" << c.real << "+i*" << c.imag << ")";
  z.real = z.real + c.real;
  z.imag = z.imag + c.imag;
  //std::cout << "= (" << z.real << "+i*" << z.imag << ")" << std::endl; 
}

Complex add_complex2(Complex z, Complex c)
{
  Complex ret;
  ret.real = z.real + c.real;
  ret.imag = z.imag + c.imag;
  return ret;
}

// Multipliziert zwei komplexe Zahlen z und c und schreibt das Ergebnis in z
void multiply_complex(Complex& z, Complex c)
{
  //std::cout << "(" << z.real << "+i*" << z.imag << ") * (" << c.real << "+i*" << c.imag << ")";
  double zimag = z.imag;
  double zreal = z.real;
  double cimag = c.imag;
  double creal = c.real;
  z.imag = (zimag * creal) + (zreal * cimag);
  z.real = (zreal * creal) - (zimag * cimag);
  //std::cout << "= (" << z.real << "+i*" << z.imag << ")" << std::endl;
}

Complex multiply_complex2(Complex z, Complex c)
{
  Complex ret;
  ret.real = z.real * c.real - z.imag * c.imag;
  ret.imag = z.real * c.imag + z.imag * c.real;
  return ret;
}

// Betrag einer komplexen Zahl
double betrag(Complex z)
{
  // TODO Nutzen Sie std::sqrt zur Wurzelberechnung
  return std::sqrt(z.real*z.real + z.imag*z.imag);
}

int grauwert(Complex c, int maxIt, double threshold)
{
  Complex z;
  z.real = 0;
  z.imag = 0;
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
    grauwert_value = (int) (std::log(Itnumber) * 100);
    //grauwert_value = 1;
  }
  //print(grauwert_value);
  return grauwert_value;
}


// TODO Funktion mandelbrot()
void mandelbrot(Canvas& canvas, double threshold,
int maxIt, std::string filename)
{
  for (int i = 0; i < canvas.vertPixels(); i++)
  {
    for (int j = 0; j < canvas.horPixels(); j++)
    {
      //std::cout << canvas.coord(i,j).real << std::endl;
      int grauwert_value = grauwert(canvas.coord(i,j), maxIt, threshold);
      canvas.writePixel(i, j , grauwert_value);
    }
  }
  canvas.write(filename);
}

int main()
{
  //int horPixels;
  //int vertPixels;
  //int maxIt;
  //int threshold;
  //Canvas::Canvas(double center_x, double center_y,double width, double height,int horPixels, int vertPixels)
  Canvas mandelbrotcanvas(-1, 0, 1000, 1000, 4000, 3000);
  //mandelbrot(Canvas& canvas, double threshold, int maxIt, std::string filename)
  mandelbrot(mandelbrotcanvas, 1000, 1000, "mandelbrotbild");
  return 0;
}