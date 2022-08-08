#include<iostream>

#include"Ptr.hh"

int g (Ptr<int> p) {
  return *p;
}

int main ()
{
  Ptr<int> q = new int(17);
  std::cout << *q << std::endl;
  int x = g(q);
  std::cout << x << std::endl;
  Ptr<int> z = new int(22);
  q = z;
  std::cout << *q << std::endl;
  // nun wird alles automatisch geloescht !
}
