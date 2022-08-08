#include "fcpp.hh"


float add(int n)
{
	float a = pow(10, n);
	float b = -pow(10, n);
	float c = pow(10, -n);

	return (a+b)+c;
}


float add2(int n)
{
	float a = pow(10, n);
	float b = -pow(10, n);
	float c = pow(10, -n);

	return a+(b+c);
}

int main()
{
	int n;
	std::cout << "Enter int n" << std::endl;
	std::cin >> n;
	print(add(n));
	print(add2(n));
	return 0;
}
