#include "fcpp.hh"

int fibIter (int letzte, int vorletzte, 
             int zaehler)
{
  return cond( zaehler==0,
    vorletzte,
    fibIter(vorletzte+letzte,letzte,zaehler-1));
}

int fib (int n)
{
  return fibIter(1,0,n);
}

int main (int argc, char** argv)
{
  return print(fib(readarg_int(argc,argv,1)));
}
