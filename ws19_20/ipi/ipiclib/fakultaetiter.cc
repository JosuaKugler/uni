#include "fcpp.hh"

int fakIter (int produkt, int zaehler, int ende)
{
  return cond( zaehler>ende,
	       produkt,
	       fakIter(produkt*zaehler,zaehler+1,ende) );
}
int fakultaet (int n)
{
  return fakIter(1,1,n);
}
int main ()
{
  return print(fakultaet(5));
}
