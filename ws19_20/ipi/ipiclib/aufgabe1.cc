#include <iostream>

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

float& SimpleFloatArray::operator[] (int i)
{
  return p[i];
}

SimpleFloatArray::SimpleFloatArray (int s, 
				    float v)
{
  n = s;
  try {
    p = new float[n];
  }
  catch (std::bad_alloc) {
    n = 0;
    throw;
  }
  for (int i=0; i<n; i=i+1) p[i]=v;
}

SimpleFloatArray::~SimpleFloatArray () { delete[] p; }

int SimpleFloatArray::numIndices () { return n; }

int SimpleFloatArray::minIndex () { return 0; }

int SimpleFloatArray::maxIndex () { return n-1; }

bool SimpleFloatArray::isMember (int i)
{
  return (i>=0 && i<n);
}

SimpleFloatArray::SimpleFloatArray (const SimpleFloatArray& a) {
  n = a.n;
  p = new float[n];
  for (int i=0; i<n; i=i+1)
    p[i]=a.p[i];
}

SimpleFloatArray& SimpleFloatArray::operator=
(const SimpleFloatArray& a)
{
  // nur bei verschiedenen Objekten ist was tun
  if (&a!=this) 
    {
      if (n!=a.n) {
        // allokiere fuer this ein 
        // Feld der Groesse a.n
        delete[] p; // altes Feld loeschen
        n = a.n;
        p = new float[n]; // keine Fehlerbeh.
      }
      for (int i=0; i<n; i=i+1) p[i]=a.p[i];
    }

  // Gebe Referenz zurueck damit a=b=c klappt
  return *this; 
}


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