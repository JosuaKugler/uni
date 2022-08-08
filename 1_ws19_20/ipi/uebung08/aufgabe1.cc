#include <iostream>

class Zahl
{
public:
  Zahl();                // Konstruktor
  Zahl( const int& n );  // int-Konstruktor
  Zahl( const Zahl& n ); // Copy-Konstruktor
  ~Zahl();               // Destruktor
  // int-Zuweisung
  Zahl& operator=( const int& n );
  // Zuweisung
  Zahl& operator=( const Zahl& n );
  // Addition
  Zahl operator+( const Zahl& n );
private:
  int z;
};

Zahl::Zahl() { std::cout << "Konstruktor aufgerufen" << std::endl; z = 0; }
Zahl::Zahl( const int& n )  { std::cout << "int-Konstruktor aufgerufen" << std::endl; z = n; }
Zahl::Zahl( const Zahl& n ) { std::cout << "Copy - Konstruktor aufgerufen" << std::endl; z = n.z; }
Zahl::~Zahl()               { std::cout << "Destruktor aufgerufen" << std::endl; }
Zahl& Zahl::operator=( const int& n )
{ std::cout << "int-Zuweisung" << std::endl; z=n;   return *this; }
Zahl& Zahl::operator=( const Zahl& n )
{ std::cout << "Zuweisung" << std::endl; z=n.z; return *this; }
Zahl Zahl::operator+( const Zahl& n )
{ std::cout << "Addition" << std::endl; return Zahl(z+n.z); }

Zahl f( Zahl a, Zahl& b) { return a+b; }

int main()
{
    std::cout << "Zeile 37:" << std::endl;
  Zahl a(3), b(4);
    std::cout << "Zeile 38:" << std::endl;
  Zahl c(a), d, e;
    std::cout << "Zeile 39:" << std::endl;
  d = 5;
      std::cout << "Zeile 40:" << std::endl;
  d = f(d,c);
    std::cout << "Zeile 41:" << std::endl;
  e = d + a + b;
      std::cout << "Zeile 42:" << std::endl;
  return 0;
}
/* @VERBOFF */
