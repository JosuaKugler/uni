#include<iostream>

// alles zum SimpleFloatArray
#include "SimpleFloatArray.hh"
#include "SimpleFloatArrayImp.cc"
#include "SimpleFloatArrayIndex.cc"
#include "SimpleFloatArrayCopyCons.cc"
#include "SimpleFloatArrayAssign.cc"

// Das Polynom
#include "Polynomial.hh"
#include "PolynomialImp.cc"
#include "PolynomialKons.cc"
#include "PolynomialEqual.cc"
#include "PolynomialEval.cc"

int main ()
{
  Polynomial p(2),q(10);

  p[0] = 1.0;
  p[1] = 1.0;
  p.print();

  q = p*p;
  q.print();

  q = p*p*p;
  q.print();
}
