#include "fcpp.hh"

unsigned int x = 93267;

unsigned int zufall ()
{
  unsigned int ia = 16807,  im = 2147483647;
  unsigned int iq = 127773, ir = 2836;
  unsigned int k;

  k = x/iq;             // LCG xneu=(a*xalt) mod m
  x = ia*(x-k*iq)-ir*k; // a = 7^5, m = 2^31-1
  if (x<0) x = x+im;    // keine lange Arithmetik
  return x;             // s. Numerical Recipes 
}                       // in C, Kap. 7.
 
unsigned int ggT (unsigned int a, unsigned int b)
{
  if (b==0) return a;
  else      return ggT(b,a%b);
}

int experiment ()
{
  unsigned int x1,x2;

  x1 = zufall(); x2 = zufall();
  if (ggT(x1,x2)==1)
    return 1;
  else
    return 0;
}
     
double montecarlo (int N)
{
  int erfolgreich=0;

  for (int i=0; i<N; i=i+1)
    erfolgreich = erfolgreich+experiment();

  return ((double)erfolgreich)/((double)N);
}

int main (int argc, char** argv) {
  print(sqrt(6.0/montecarlo(readarg_int(argc,argv,1))));
}
