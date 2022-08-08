#include <vector>
#include <iostream>

template <class T>
class Function
{
public:
    virtual ~Function(){};
    virtual T operator()(T &x) = 0;
};

template <class T, int n>
class Vector : public std::vector<T>
{
public:
    Vector();
    Vector(T entry);
    //Addition zweier Vektoren
    template <class T2>
    Vector<T, n> operator+(const Vector<T2, n> &y);

    //Skalarprodukt
    template <class T2>
    T operator*(const Vector<T2, n> &y);

    //Skalarmultiplikation
    template <class T2>
    Vector<T, n> operator*(T2 y);

    //Anwenden einer Funktion
    void apply(Function<T> &func);

    //minimum
    T min();
    //maximum
    T max();
    //mittelwert
    T mittel();

    void print();
};

template <class T, int n>
Vector<T, n>::Vector() : std::vector<T>(n) {}

template <class T, int n>
Vector<T, n>::Vector(T entry) : std::vector<T>(n, entry) {}

template <class T, int n>
template <class T2>
Vector<T, n> Vector<T, n>::operator+(const Vector<T2, n> &y)
{
    Vector<T, n> ret;
    for (size_t i = 0; i < n; i++)
    {
        ret[i] = (*this)[i] + y[i];
    }
    return ret;
}

template <class T, int n>
template <class T2>
T Vector<T, n>::operator*(const Vector<T2, n> &y)
{
    T ret = 0;
    for (size_t i = 0; i < n; i++)
    {
        ret += (*this)[i] * y[i];
    }
    return ret;
}

template <class T, int n>
template <class T2>
Vector<T, n> Vector<T, n>::operator*(T2 y)
{
    Vector<T, n> ret;
    for (size_t i = 0; i < n; i++)
    {
        ret[i] = (*this)[i] * y;
    }
    return ret;
}

template <class T, int n>
void Vector<T, n>::apply(Function<T> &func)
{
    for (size_t i = 0; i < n; i++)
    {
        (*this)[i] = func((*this)[i]);
    }
}

template <class T, int n>
T Vector<T, n>::min()
{
    T ret = (*this)[0];
    for (size_t i = 1; i < n; i++)
    {
        if ((*this)[i] < ret)
        {
            ret = (*this)[i];
        }
    }
    return ret;
}

template <class T, int n>
T Vector<T, n>::max()
{
    T ret = (*this)[0];
    for (size_t i = 1; i < n; i++)
    {
        if ((*this)[i] > ret)
        {
            ret = (*this)[i];
        }
    }
    return ret;
}

template <class T, int n>
T Vector<T, n>::mittel()
{
    T sum = 0;
    for (size_t i = 1; i < n; i++)
    {
        sum = sum + (*this)[i];
    }
    T ret = sum / n;
    return ret;
}

template <class T, int n>
void Vector<T, n>::print()
{
    std::cout << "[" << (*this)[0];
    for (size_t i = 1; i < n; ++i)
    {
        std::cout << ", " << (*this)[i];
    }
    std::cout << "]";
}

int main()
{
    Vector<double, 3> a(0.0);
    a[0] = 1.0;
    a[1] = 2.0;
    a[2] = 3.0;
    a.print();
    std::cout << std::endl;
    Vector<float, 3> b(0.0);
    b[0] = 1.0;
    b[1] = 2.0;
    b[2] = 3.0;
    b.print();
    std::cout << std::endl;
    float result = b * a;
    a = a * result;
    a.print();
    class Quadrat : public Function<double>
    {
    public:
        virtual double operator()(double &x) { return x * x; }
    };
    Quadrat quadrat;
    a.apply(quadrat);
    a.print();
    a = a + b * -200;
    a.print();
    return 0;
}