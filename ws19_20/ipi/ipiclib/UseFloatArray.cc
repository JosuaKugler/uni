#include <iostream>

#include "FloatArray.hh"
#include "DFA.cc"
#include "LFA.cc"

void polyshow (FloatArray& f) {
  for (int i=f.minIndex(); i<=f.maxIndex(); i=i+1)
    if (f.isMember(i)  && f[i]!=0.0)
      std::cout << "+" << f[i] << "*x^" << i;
  std::cout << std::endl;
}

void polymul (FloatArray& a, FloatArray& b, FloatArray& c) {
  // Loesche a
  for (int i=a.minIndex(); i<=a.maxIndex(); i=i+1)
    if (a.isMember(i))
      a[i] = 0.0;

  // a = b*c
  for (int i=b.minIndex(); i<=b.maxIndex(); i=i+1)
    if (b.isMember(i))
      for (int j=c.minIndex(); j<=c.maxIndex(); j=j+1)
        if (c.isMember(j))
          a[i+j] = a[i+j]+b[i]*c[j];
}

int main ()
{
  // funktioniert mit einer der folgenden Zeilen:
  // DynamicFloatArray f,g;
  ListFloatArray f,g;
    
  f[0] = 1.0; f[100] = 1.0;

  polymul(g,f,f); 
  polymul(f,g,g);
  polymul(g,f,f); 
  polymul(f,g,g); // f=(1+x^100)^16

  polyshow(f);
}
