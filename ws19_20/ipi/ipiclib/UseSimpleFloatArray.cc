#include <iostream>
#include "SimpleFloatArray.hh"
#include "SimpleFloatArrayImp.cc"
#include "SimpleFloatArrayIndex.cc"
#include "SimpleFloatArrayCopyCons.cc"
#include "SimpleFloatArrayAssign.cc"

void show (SimpleFloatArray f) {
  std::cout << "#( ";
  for (int i=f.minIndex(); i<=f.maxIndex(); i++)
    std::cout << f[i] << " ";
  std::cout << ")" << std::endl;
}   

int main () {
  SimpleFloatArray a(10,0.0); // erzeuge Felder
  SimpleFloatArray b(5,5.0);

  for (int i=a.minIndex(); i<=a.maxIndex(); i++) 
    a[i] = i;

  show(a); // call by value, ruft Copy-Konstruktor
  b = a;   // ruft operator= von b
  show(b);

  // hier wird der Destruktor beider Objekte gerufen
}
