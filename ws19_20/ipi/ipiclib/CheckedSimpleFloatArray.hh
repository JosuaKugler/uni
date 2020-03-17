class CheckedSimpleFloatArray : 
  public SimpleFloatArray {
public:
  CheckedSimpleFloatArray (int s, float f);

  // Default-Versionen von copy Konstruktor, Zuweisungsoperator
  // und Destruktor sind OK

  // Indizierter Zugriff mit Indexprüfung
  float& operator[](int i);
} ;
