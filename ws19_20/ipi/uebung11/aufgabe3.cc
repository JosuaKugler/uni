#include <iostream>
#include <cmath>

class Wurzel
{
public:
    double operator()(double x)
    {
        return std::sqrt(x);
    }
};

template <class Funktion>
double trapezregel(int n, double a, double b, Funktion& f)
{
    double h = (b-a)/n;
    double sum = 0;
    for (size_t i = 1; i < n; i++)
    {
        sum += f(a + i*h);
    }
    return h/2 * (f(a) + 2 * sum + f(b));
}

int main()
{
    Wurzel wurzel = Wurzel();
    std::cout << trapezregel<Wurzel>(100, 0, 1.5, wurzel);
    return 0;
}