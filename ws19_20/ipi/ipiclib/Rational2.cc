#include "fcpp.hh"

struct Rational {
  int zaehler;
  int nenner;
} ;

// Abstraktion: Konstruktor und Selektoren

Rational erzeuge_rat (int z, int n)
{
  Rational t;
  t.zaehler = z;
  t.nenner = n;
  return t;
}

int zaehler (Rational q)
{
  return q.zaehler;
}

int nenner (Rational q)
{
  return q.nenner;
}

// Arithmetische Operationen

Rational add_rat (Rational p, Rational q)
{
  return erzeuge_rat(
    zaehler(p)*nenner(q)+zaehler(q)*nenner(p),
    nenner(p)*nenner(q));
}

Rational sub_rat (Rational p, Rational q)
{
  return erzeuge_rat(
    zaehler(p)*nenner(q)-zaehler(q)*nenner(p),
    nenner(p)*nenner(q));
}

Rational mul_rat (Rational p, Rational q)
{
  return erzeuge_rat(zaehler(p)*zaehler(q),
		     nenner(p)*nenner(q));
}

Rational div_rat (Rational p, Rational q)
{
  return erzeuge_rat(zaehler(p)*nenner(q),
		     nenner(p)*zaehler(q));
}

void drucke_rat (Rational p)
{
  print(zaehler(p),"/",nenner(p),0);
}

int main ()
{
  Rational p = erzeuge_rat(3,4);
  Rational q = erzeuge_rat(5,3);
  drucke_rat(p); drucke_rat(q);
    
  // p*q+p-p*p
  Rational r = sub_rat(add_rat(mul_rat(p,q), p),
		       mul_rat(p,p));
  drucke_rat(r);
  return 0;
}
