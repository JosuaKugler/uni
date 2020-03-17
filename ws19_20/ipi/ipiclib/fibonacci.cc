#include "fcpp.hh"

int fib (int n)
{
  return cond( n==0, 0,
	       cond( n==1, 1,
		     fib(n-1)+fib(n-2) ) ); 
}

int main (int argc, char** argv)
{
  return print(fib(readarg_int(argc,argv,1)));
}
