#include "fcpp.hh"

int teiler(int a, int b)
{
	return cond(a % b == 0, b, 0);
}

int teilersumme(int gesamtzahl, int max)
{
	return teiler(gesamtzahl, max) + cond(max > 1, teilersumme(gesamtzahl, max-1), 0);
}

bool vollkommen(int zahl)
{
	return cond(teilersumme(zahl, zahl-1) == zahl, true, false);
}

int main()
{
	return print(vollkommen(497));
}
