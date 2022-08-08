#include<iostream>
#include "fcpp.hh"       // fuer print
#include "Rational.hh"
#include "Rational.cc"
#include "RationalOutput.cc"

int main () {
  Rational p(3,4), q(5,3);

  std::cout << p << " " << q << std::endl; 
  std::cout << (p+q*p)*p*p << std::endl;
  return 0;
}
