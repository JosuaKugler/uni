#include "fcpp.hh"

bool gut_genug (double xn, double a) {
  return fabs(xn*xn-a)<=1E-15;
}

double wurzelIter (double xn, double a) {
  return cond( gut_genug(xn,a),
	       xn,
	       wurzelIter(0.5*(xn+a/xn),a) );
}

double wurzel (double a)
{
  return wurzelIter(1.0,a);
}

int main (int argc, char** argv)
{
  return print(wurzel(readarg_double(argc,argv,1)));
}
