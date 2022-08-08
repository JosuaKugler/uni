#include "fcpp.hh"

float determinante(float a, float b, float c, float d)
{
        return a * d - b * c;
}

double determinante2(double a, double b, double c, double d)
{
        return a * d - b * c;
}

int main ()
{       
        print(determinante2(100, 0.01, -0.01, 100));
        return 0;
}   
