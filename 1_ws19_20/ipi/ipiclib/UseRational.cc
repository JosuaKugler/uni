#include "fcpp.hh"       // fuer print
#include "Rational.hh"
#include "Rational.cc"

int main () {
    Rational p(3,4), q(5,3), r;

    p.print(); q.print();
    r = (p+q*p)*p*p;
    r.print();
    
    return 0;
}
