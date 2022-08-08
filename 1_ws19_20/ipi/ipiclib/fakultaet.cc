#include "fcpp.hh"

int fakultaet (int n)
{
  return cond( n<=1, 1, n*fakultaet(n-1) );
}

int main ()
{
  return print(fakultaet(5));
}
