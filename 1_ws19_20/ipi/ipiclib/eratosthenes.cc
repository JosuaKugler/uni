#include "fcpp.hh"

int main ()
{
    const int n = 500000;
    bool prim[n];

    // Initialisierung
    prim[0] = false;
    prim[1] = false;
    for (int i=2; i<n; i=i+1)
        prim[i] = true;

    // Sieb
    for (int i=2; i<=sqrt((double) n); i=i+1)
        if (prim[i])
            for (int j=2*i; j<n; j=j+i)
                prim[j] = false;

    // Ausgabe
    int m=0;
    for (int i=0; i<n; i=i+1)
      if (prim[i]) 
        m = m+1;
    print("Anzahl Primzahlen:");
    print(m);
    
    return 0;
}
