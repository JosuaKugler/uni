#include <iostream>
#include <cmath>

bool teilt(int a, int b)
//ermittelt, ob b a teilt
{
    if (b%a == 0)
    {
        return true;
    }
    return false;
}

int main()
{
    //zu untersuchende Zahl
    const int n = 361;
    //feld[i] gibt an, durch welche potenz von i n teilbar ist
    int feld[n];
    //Initialisierung
    for (int i = 0; i<n; ++i)
    {
        feld[i] = 0;
    }
    //immer, wenn ein weiterer Teiler von n gefunden wird, wird restzahl durch diesen Teiler geteil.
    //Daher ist restzahl immer gleich n geteilt durch das Produkt aller bisher ermittelten primfaktoren
    int restzahl = n;
    for (int i = 2; i<=sqrt((double) n); ++i)
    {
        //findet heraus, wie oft i restzahl noch teilt
        while (teilt(i,restzahl))
        {
            feld[i] = feld[i] + 1;
            restzahl = restzahl/i;
        }
    }
    //wenn in der Primfaktorzerlegung noch eine Primzahl groesser als sqrt(n) enthalten ist, 
    //so wird sie in diesem Schritt noch ausgegeben
    if (restzahl != 1)
    {
        feld[restzahl] = 1;
    }
    //Ausgabe
    for (int i = 0; i<n; ++i)
    {
        if (feld[i] > 0)
        {
            std::cout << i << "^" << feld[i] << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}