#include<cassert>
#include<iostream>

#include"Array.hh"
#include"DLL.hh"
#include"Zufall.cc"

int main () {
  Zufall z(87124);
  Array<int> a(5);
  DLList<int> l;

  // Erzeuge Array und Liste mit 5 Zufallszahlen
  for (int i=0; i<5; i=i+1) a[i] = z.ziehe_zahl();
  for (int i=0; i<5; i=i+1)
    l.insert(l.end(), z.ziehe_zahl());

  // Benutzung
  for (Array<int>::Iterator i=a.begin();
       i!=a.end(); i++)
    std::cout << *i << std::endl;
  std::cout << std::endl;
  for (DLList<int>::Iterator i=l.begin();
       i!=l.end(); i++)
    std::cout << *i << std::endl;
}
