#include "fcpp.hh"

enum Zustand { neu, gebraucht, alt, kaputt };

void druckeZustand (Zustand x) {
  if (x==neu)       print("neu");
  if (x==gebraucht) print("gebraucht");
  if (x==alt)       print("alt");
  if (x==kaputt)    print("kaputt");
}

int main () {druckeZustand(alt);}
