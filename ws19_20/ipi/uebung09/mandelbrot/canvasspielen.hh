#include <string>
#include <iostream>
#include "pgm.hh"
 
typedef long double my_double;

struct Complex
{
  my_double real;
  my_double imag;
};

class Canvas
{
public :
  // Konstruktor, erzeuge int* _pixels
  Canvas(my_double center_x, my_double center_y,
         my_double width, my_double height,
         int horPixels, int vertPixels, Complex c, my_double zoom);

  // Destruktor, raeume int* _pixels auf
  ~Canvas();

  // gibt die Breite des Bildes zurueck
  my_double width();

  // gibt die Hoehe des Bildes zurueck
  my_double height();

  // gibt die Anzahl an horizontalen Pixeln
  int horPixels();

  // gibt die Anzahl an vertikalen Pixeln
  int vertPixels();

  // gebe die Koordinaten des Pixels (i,j) als Complex zurueck
  Complex coord(int i, int j);

  // schreibe value an den Pixel (i,j)
  // Ueberlegen Sie wie aus (i,j) den flachen Index bei row-major bekommen
  void writePixel(int i, int j, int value);

  // Zugang zum Pixel (i,j) im 1D Array
  // Ueberlegen Sie wie aus (i,j) den flachen Index bei row-major bekommen
  int operator()(int i, int j);

  //debugging stuff
  void printPixels();

  //get parameter c
  Complex get_c();

  // schreibe Bild mit Dateinamen filename
  void write(std::string filename);
private :
  my_double _center_x;
  my_double _center_y;
  my_double _width;
  my_double _height;
  Complex _c;
  my_double _zoom;
  int _horPixels;
  int _vertPixels;
  int* _pixels;
};

Canvas::Canvas(my_double center_x, my_double center_y,
         my_double width, my_double height,
         int horPixels, int vertPixels, Complex c, my_double zoom)
         {
          _center_x = center_x;
          _center_y = center_y;
          _width = width;
          _height = height;
          _horPixels = horPixels;
          _vertPixels = vertPixels;
          _c = c;
          _zoom = zoom;
          _pixels = new int[horPixels * vertPixels];
          for (int i = 0; i < horPixels * vertPixels; i++)
           {
             _pixels[i] = 0;
           }
         }

Canvas::~Canvas()
{
  delete _pixels;
}

my_double Canvas::width(){return _width;};

my_double Canvas::height(){return _height;};

int Canvas::horPixels(){return _horPixels;};

int Canvas::vertPixels(){return _vertPixels;};

Complex Canvas::coord(int i, int j)
{
  Complex z;
  z.real = ((my_double) j - (my_double) _horPixels/2 - 1)/(1000 * _zoom);
  z.imag = ((my_double) i - (my_double) _vertPixels/2)/(1000 * _zoom);
  return z;
}

void Canvas::writePixel(int i, int j, int value)
{
  int position = i*_horPixels + j;
  _pixels[position] = value;
}

int Canvas::operator()(int i, int j)
{
  int position = i*_horPixels + j;
  return _pixels[position];
}

// diese Methode ist bereits implementiert
void Canvas::write(std::string filename)
{
  write_pgm(_pixels,_horPixels,_vertPixels,filename);
}

void Canvas::printPixels()
{
  for (int i = 0; i < _vertPixels * _horPixels; i++)
  {
    print(_pixels[i]);
  }
}

Complex Canvas::get_c()
{
  return _c;
}