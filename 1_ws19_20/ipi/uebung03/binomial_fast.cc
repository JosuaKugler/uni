#include "fcpp.hh"

int factorial(int f)
{
	return cond( f == 0, 1,
		cond( f== 1, 1, factorial(f - 1) * f)); 
}

int binomial_fast(int n, int k)
{
	return 	( factorial( n)) / (( factorial( k)) * ( factorial( n - k)));
}


int main (int argc, char** argv)
{
	return print( binomial_fast( readarg_int( argc, argv, 1),
				      readarg_int( argc, argv, 2)));
}
