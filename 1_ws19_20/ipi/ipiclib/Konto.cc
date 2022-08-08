#include "fcpp.hh"
  
class Konto {
public:
  Konto (int start);    // Konstruktor
  ~Konto ();            // Destruktor   
  int kontostand ();
  int abheben (int betrag);
private:
  int bilanz;
} ;
  
Konto::Konto (int startkapital)
{
  bilanz = startkapital;
  print("Konto mit ",bilanz," eingerichtet",0);
}
  
Konto::~Konto ()
{
  print("Konto mit ",bilanz," aufgelöst",0);
}
  
int Konto::kontostand () {
  return bilanz;
}
  
int Konto::abheben (int betrag)
{
  bilanz = bilanz - betrag;
  return bilanz;
}
  
int main ()
{
  Konto k1(100), k2(200);
  
  k1.abheben(50);
  k2.abheben(300);
}
