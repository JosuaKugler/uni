#include <iostream>

bool deck_check(int deck[], int n) 
{
    for (int i = 0; i< n; ++i)
    {
        if (deck[i] != i) //Deck ist im Anfangszustand, wenn deck[i] = i
        {
            return false;
        }
    }
    return true;
}

int perfectout(int n){ //Initialisierung vom Deck
    int normaldeck[n];
    for (int i = 0; i< n; ++i)
    {
        normaldeck[i] = i;
    }
    int counter = 0; //Zählt die Anzahl der Mischvorgänge
    bool deckcheck = false;
    while (deckcheck == false)
    {
        counter = counter + 1;
        int firstlen; //Länge des ersten Teilfeldes
        int secondlen; //Länge des zweiten Teilfeldes
        if (n%2 == 1){
            firstlen = (n+1)/2;
            secondlen = (n-1)/2;
        }
        else
        {
            firstlen = n/2;
            secondlen = n/2;
        }
        int firstarray[firstlen]; //Erstes Teilfeld
        int secondarray[secondlen]; //Zweites " "
        for (int i = 0; i < n; ++i)
        {
            if (i < firstlen)
            {
                firstarray[i] = normaldeck[i]; //Ersten firstlen Einträge werden in das erste Feld geschrieben 
            }
            else
            {
                secondarray[i-firstlen] = normaldeck[i]; //alle anderen in das Zweite
            }
        }
        for (int i = 0; i < n; ++i) // Hier wird das Deck abwechselnd mit Einträgen aus dem ersten und zweiten Deck gefüllt 
        {
            if (i % 2 == 0)
            {
                normaldeck[i] = firstarray[i/2];
            }
            else
            {
                normaldeck[i] = secondarray[(i-1)/2];
            }
        }
        deckcheck = deck_check(normaldeck, n);//Nun wird überprüft, ob sich das Deck in seinem Anfangszustand befindet
    }
    return counter;
}

int perfectin(int n){ //analog zu perfektout
    int normaldeck[n];
    for (int i = 0; i< n; ++i)
    {
        normaldeck[i] = i;
    }
    int counter = 0;
    bool deckcheck = false;
    while (deckcheck == false)
    {
        counter = counter + 1;
        int firstlen;
        int secondlen;
        if (n%2 == 1){
            firstlen = (n-1)/2;
            secondlen = (n+1)/2;
        }
        else
        {
            firstlen = n/2;
            secondlen = n/2;
        }
        int firstarray[firstlen];
        int secondarray[secondlen];
        for (int i = 0; i < n; ++i)
        {
            if (i < firstlen)
            {
                firstarray[i] = normaldeck[i];
            }
            else
            {
                secondarray[i-firstlen] = normaldeck[i];
            }
        }
        for (int i = 0; i < n; ++i)
        {
            if (i % 2 == 0)
            {
                normaldeck[i] = secondarray[i/2];
            }
            else
            {
                normaldeck[i] = firstarray[(i-1)/2];
            }
        }
        deckcheck = deck_check(normaldeck, n);
    }
    return counter;
}

int main()
{
    int decklength;
    std::cin >> decklength;
    int outcounter = perfectout(decklength);
    int incounter = perfectin(decklength);
    std::cout << outcounter << std::endl << incounter << std::endl;
    return 0;
}