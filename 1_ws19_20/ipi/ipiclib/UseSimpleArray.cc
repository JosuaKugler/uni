#include<iostream>

#include "SimpleArray.hh"
#include "SimpleArrayImp.cc"

int main ()
{
  SimpleArray<float> a(10,0.0); // erzeuge
  SimpleArray<int> b(25,5);     // Felder

  for (int i=a.minIndex(); i<=a.maxIndex(); i++) 
    a[i] = i;
  for (int i=b.minIndex(); i<=b.maxIndex(); i++) 
    b[i] = i;

  std::cout << a << std::endl << b << std::endl;
    
  // hier wird der Destruktor gerufen
}
