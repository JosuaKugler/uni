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
