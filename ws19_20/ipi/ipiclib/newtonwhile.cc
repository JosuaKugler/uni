#include "fcpp.hh"

double wurzel (double a)
  {
      double x=1.0;
   
      while (fabs(x*x-a)>1E-12)
          x = 0.5*(x+a/x);
      return x;
  }

int main ()
{
  return print(wurzel(2.0));
}
