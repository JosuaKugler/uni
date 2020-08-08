#include<iostream>
#include "../hdnum/hdnum.hh"



void getCubicSpline(hdnum::DenseMatrix<double>& coeff, hdnum::Vector<double> x, hdnum::Vector<double> y)
{
    int n = x.size() -1;
    hdnum::Vector<double> h(n, 0);
    for (size_t i = 0; i < n; i++)
    {
        h[i] = x[i+1]- x[i];
    }
    //std::cout << "h: " <<  h << std::endl;
    //calculate coeff[i][2] into a2[i]
    hdnum::Vector<double> a2(n-1,0);
    hdnum::Vector<double> b(n-1,0);
    //setup matrix A
    hdnum::DenseMatrix<double> A(n-1, n-1);
    for (size_t i = 0; i < n-1; i++)
    {
        A[i][i] = 2 * (h[i] + h[i+1]);
        if (i > 0) A[i][i-1] = h[i];
        if (i < n-1) A[i][i+1] = h[i+1];
        b[i] = 3 * (((y[i+2] - y[i+1])/h[i+1]) - (y[i+1]-y[i])/h[i]);
    }
    //std::cout << A << ", " << b << std::endl;
    std::cout << "" << std::endl;
    hdnum::linsolve(A, a2, b);

    //std::cout << a2;

    for (size_t i = 0; i < n; i++)
    {
        coeff[i][0] = y[i+1];
        if (i == 0) coeff[i][1] = (y[i+1] - y[i])/h[i] + h[i]/3*(2*a2[i] + 0);
        else coeff[i][1] = (y[i+1] - y[i])/h[i] + h[i]/3*(2*a2[i] + a2[i-1]);
        coeff[i][2] = a2[i];
        if (i == 0) coeff[i][3] = (a2[i] - 0)/(3*h[i]);
        else coeff[i][3] = (a2[i] - a2[i-1])/(3*h[i]);
    }
    //std::cout << coeff;
}

double evaluateCubicSpline(hdnum::DenseMatrix<double> coeff, hdnum::Vector<double> xs, double x)
{
    int n = xs.size() -1;
    int index = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (xs[i] <= x)
        {
            index = i;
            //std::cout << xs[i] << "<= " << x << "<=" << xs[i+1] << std::endl;
        }
    }
    double v = x-xs[index+1];
    return coeff[index][0] + coeff[index][1] * v + coeff[index][2] * v*v + coeff[index][3] * v*v*v;
}

void aufgabe4b(){
    hdnum::Vector<double> x(3,0);
    hdnum::Vector<double> y(3,0);
    x[0] = 0; x[1] = 1; x[2] = 2;
    y[0] = 0; y[1] = 1; y[2] = 8;
    hdnum::DenseMatrix<double> coeff(2,4);
    //std::cout << x << ", " << y << ", " << coeff << std::endl;
    getCubicSpline(coeff, x, y);
    std::cout << coeff;
    std::cout << evaluateCubicSpline(coeff, x, 1);
}

void aufgabe5c(){
    hdnum::Vector<double> x(13,0);
    x[0] = 3.75; x[1] = 3.75; x[2] = 2.25; x[3] = 1.25; x[4] = 0.25; x[5] = 0.75; x[6] = 4.00; x[7] = 5.50; x[8] = 6.25; x[9] = 9.00; x[10] = 12.50; x[11] = 12.75; x[12] = 12.25;
    hdnum::Vector<double> y(13,0);
    y[0] = 0.25; y[1] = 1.50; y[2] = 3.25; y[3] = 4.25; y[4] = 4.65; y[5] = 4.83; y[6] = 2.50; y[7] = 3.25; y[8] = 3.65; y[9] = 3.00; y[10] = 1.25; y[11] = 2.15; y[12] = 3.50;
    hdnum::Vector<double> t(13,0);
    for (size_t i = 1; i < 13; i++)
    {
        t[i] = t[i-1] + sqrt((x[i]-x[i-1])*(x[i]-x[i-1]) + (y[i] - y[i-1])*(y[i] - y[i-1]));
    }
    //std::cout << x << y << t;
    hdnum::DenseMatrix<double> psicoeff(12,4);
    hdnum::DenseMatrix<double> phicoeff(12,4);
    getCubicSpline(phicoeff, t, x);
    getCubicSpline(psicoeff, t, y);

    hdnum::Vector<double> xcoords(101, 0);
    hdnum::Vector<double> ycoords(101, 0);
    for (size_t i = 0; i < 101; i++)
    {
        ycoords[i] = evaluateCubicSpline(psicoeff, t, t[12]/100 * i);
        xcoords[i] = evaluateCubicSpline(phicoeff, t, t[12]/100 * i);
    }
    
    for (size_t i = 0; i < 101; i++)
    {
        std::cout << xcoords[i] << " " << ycoords[i] << std::endl;
    }
}

int main()
{
    aufgabe5c();
    return 0;
}
