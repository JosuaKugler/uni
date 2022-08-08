class SimpleFloatArray { 
public:
  // Neues Feld mit s Elementen, I=[0,s-1]
  SimpleFloatArray (int s, float f);

  // Copy-Konstruktor
  SimpleFloatArray (const SimpleFloatArray&);

  // Zuweisung von Feldern
  SimpleFloatArray& operator= (const SimpleFloatArray&);

  // Destruktor: Gebe Speicher frei
  ~SimpleFloatArray();

  // Indizierter Zugriff auf Feldelemente
  // keine Ueberpruefung ob Index erlaubt
  float& operator[](int i);

  // Anzahl der Indizes in der Indexmenge
  int numIndices ();

  // kleinster Index
  int minIndex ();

  // größter Index
  int maxIndex ();

  // Ist der Index in der Indexmenge?
  bool isMember (int i);

private:
  int n;      // Anzahl Elemente
  float *p;   // Zeiger auf built-in array
} ;
