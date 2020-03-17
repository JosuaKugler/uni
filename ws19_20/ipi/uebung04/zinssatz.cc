#include "fcpp.hh"

float zins(float z, int n)
{
	return pow(1 + z * pow(n, -1), n) - 1; 
}

double zins2(double z, int n)
{
	return pow(1 + z/n, n) - 1; 
}

void ausgabe(int n)
{
	print(n);
	print(zins(0.06, n));
	print(exp(0.06) - 1 - zins(0.06, n));
	print(zins2(0.06, n));
	print(exp(0.06) - 1 - zins2(0.06, n));
}

int main()
{
	ausgabe(1);
	ausgabe(4);
	ausgabe(12);
	ausgabe(356);
	ausgabe(365*24);
	ausgabe(365*24*60);
	ausgabe(365*24*60*2);	
	ausgabe(365*24*60*60);
	return 0;
}

