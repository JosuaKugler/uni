#include<cassert>
#include<iostream>
#include"DLL.hh"
#include"Zufall.cc"

int main ()
{
    Zufall z(87124);
    DLList<int> l1,l2,l3;

    // Erzeuge 3 Listen mit je 5 Zufallszahlen
    for (int i=0; i<5; i=i+1)
        l1.insert(l1.end(), i);
    for (int i=0; i<5; i=i+1)
        l2.insert(l2.end(), z.ziehe_zahl());
    for (int i=0; i<5; i=i+1)
        l3.insert(l3.end(), z.ziehe_zahl());

    // Loesche alle geraden in der ersten Liste
    DLList<int>::Iterator i,j;
    i=l1.begin();
    while (i!=l1.end())
    {
        j=i; // merke aktuelles Element 
        ++i; // gehe zum naechsten
        if (*j%2==0) l1.erase(j);
    }

    // Liste von Listen ...
    DLList<DLList<int> > ll;
    ll.insert(ll.end(),l1);
    ll.insert(ll.end(),l2);
    ll.insert(ll.end(),l3);
    std::cout << ll << std::endl;
    std::cout << "Laenge: " << ll.size() << std::endl;
}
