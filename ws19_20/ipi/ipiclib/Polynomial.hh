class Polynomial : 
  public SimpleFloatArray {
public:
  // konstruiere Polynom vom Grad n
  Polynomial (int n);

  // Default-Destruktor ist ok
  // Default-Copy-Konstruktor ist ok
  // Default-Zuweisung ist ok

  // Grad des Polynoms
  int degree ();

  // Auswertung
  float eval (float x);

  // Addition von Polynomen
  Polynomial operator+ (Polynomial q);

  // Multiplikation von Polynomen
  Polynomial operator* (Polynomial q);

  // Gleichheit
  bool operator== (Polynomial q);

  // drucke Polynom
  void print ();
} ;
