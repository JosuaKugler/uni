#include<iostream>
#include"../hdnum/hdnum.hh"

//wir benutzen das Neville-Aitken-Schema

template<class T>
T interpolate(int n, hdnum::Vector<T> x, hdnum::Vector<T> y, T xi)
{
    for (size_t i = 0; i < n; i++)
    {
        if (x[i] == xi)
            return y[i];
    }
    //\xi \neq x_i
    hdnum::Vector<T> p(y);
    for (int k = 1; k < n; k++)
    {
        for (int i = 0; i < n-k; i++)
        {
            p[i] += (p[i] - p[i+1])/((xi - x[i+k])/(xi - x[i]) - 1);
        }
    }
    return p[0];
}

void test()
{
    hdnum::Vector<double> x(4);
    x[0] = 55.7;
    x[1] = 57.7;
    x[2] = 59.3;
    x[3] = 62.6;

    hdnum::Vector<double> y(4);
    y[0] = 1048;
    y[1] = 1080;
    y[2] = 1111;
    y[3] = 1196;

    double xi = 61.7;

    double e = interpolate(4, x, y, xi);
    std::cout << e << std::endl;
}

template<class T>
T f1(T x) {
    return 1/(1 + x*x);
} 

template<class T>
T f2(T x) {
    return sqrt(abs(x));
} 

template<class T>
hdnum::Vector<T> aufgabeb(int n, int N, bool oneortwo) {
    hdnum::Vector<T> x(n);
    hdnum::Vector<T> y(n);
    for (size_t i = 0; i < n; i++)
    {
        x[i] = -1 + i*2/((double) N);
        if (oneortwo)
            y[i] = f1(x[i]);
        else 
            y[i] = f2(x[i]);
    }
    hdnum::Vector<T> densex(N);
    for (size_t i = 0; i < N; i++)
    {
        densex[i] = -1 + i*2/((double) N);
    }
    hdnum::Vector<T> yinterpolate(N);
    for (size_t i = 0; i < N; i++)
    {
        yinterpolate[i] = interpolate(n, x, y, densex[i]);
    }
    return yinterpolate;
}

int main()
{
    int N = 1000;
    int n = 5;
    hdnum::Vector<double> y1_5 = aufgabeb<double>(n, N, true);
    hdnum::Vector<double> y2_5 = aufgabeb<double>(n, N, false);
    n = 10;
    hdnum::Vector<double> y1_10 = aufgabeb<double>(n, N, true);
    hdnum::Vector<double> y2_10 = aufgabeb<double>(n, N, false);
    n = 20;
    hdnum::Vector<double> y1_20 = aufgabeb<double>(n, N, true);
    hdnum::Vector<double> y2_20 = aufgabeb<double>(n, N, false);

    for (size_t i = N/4; i < 3*N/4; i++)
    {
        std::cout << -1 + i *  2/((double) N) << ", " << y1_5[i] << ", " << y2_5[i] << ", " << y1_10[i] << ", " << y2_10[i] << ", " << y1_20[i] << ", " << y2_20[i] << std::endl;
    }
    return 0;
}
