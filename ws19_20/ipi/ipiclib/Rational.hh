class Rational {
private:
  int n,d;
  int ggT (int a, int b);
public:
  // (lesender) Zugriff auf Zaehler und Nenner
  int numerator ();
  int denominator ();
  
  // Konstruktoren
  Rational (int num, int denom); // rational
  Rational (int num);            // ganz
  Rational ();                   // Null
  
  // Ausgabe
  void print ();
  
  // Operatoren
  Rational operator+ (Rational q);
  Rational operator- (Rational q);
  Rational operator* (Rational q);
  Rational operator/ (Rational q);
} ;
