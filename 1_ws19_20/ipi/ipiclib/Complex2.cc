#include "fcpp.hh"

struct Complex {
  float real;
  float imag;
} ;

Complex erzeuge_complex (float re, float im)
{
  Complex t;
  t.real = re; t.imag = im;
  return t;
}
float real (Complex q) {return q.real;}
float imag (Complex q) {return q.imag;}

Complex add_complex (Complex p, Complex q)
{
  return erzeuge_complex(real(p) + real(q),
			 imag(p) + imag(q));
}

// etc

void drucke_complex (Complex p)
{
  print(real(p),"+i*",imag(p),0);
}

int main ()
{
  Complex p = erzeuge_complex(3.0,4.0);
  Complex q = erzeuge_complex(5.0,3.0);
  drucke_complex(p);
  drucke_complex(q);
  drucke_complex(add_complex(p,q));
}
