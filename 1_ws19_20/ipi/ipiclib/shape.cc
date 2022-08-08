#include<iostream>
#include<cmath>

const double pi = 3.1415926536;

class Shape
{
public:
  virtual ~Shape () {};
  virtual double area () = 0;
  virtual double diameter () = 0;
  virtual double circumference () = 0;
};

// works on every shape 
double circumference_to_area (Shape &shape) {
  return shape.circumference()/shape.area();
}

class Circle : public Shape {
public:
  Circle (double r) {radius = r;}
  virtual double area () {
    return pi*radius*radius;
  }
  virtual double diameter () {
    return 2*radius;
  }
  virtual double circumference () {
    return 2*pi*radius;
  }
private:
  double radius;
};

class Rectangle : public Shape {
public:
  Rectangle (double aa, double bb) {
    a = aa; b = bb;
  }
  virtual double area () {return a*b;}
  virtual double diameter () {
    return sqrt(a*a+b*b);
  }
  virtual double circumference () {
    return 2*(a+b);
  }
private:
  double a, b;
};

int main ()
{
  Rectangle unit_square(1.0, 1.0);
  Circle unit_circle(1.0);
  Circle unit_area_circle(1.0/sqrt(pi));

  std::cout << "Das Verhältnis von Umfang zu Fläche beträgt\n";
  std::cout << "Einheitsquadrat:    "
	    << circumference_to_area(unit_square) 
	    << std::endl;
  std::cout << "Kreis mit Fläche 1: "
	    << circumference_to_area(unit_area_circle) 
	    << std::endl;
  std::cout << "Einheitskreis:      "
	    << circumference_to_area(unit_circle) 
	    << std::endl;
  return 0;
}
