#include "fcpp.hh"

int konto; // die GLOBALE Variable

void einrichten (int betrag)
{
  konto = betrag;
}

int kontostand ()
{
  return konto;
}

int abheben (int betrag)
{
  konto = konto-betrag;
  return konto;
}

int main ()
{
  einrichten(100);
  print(abheben(25));
  print(abheben(25));
  print(abheben(25));
}
