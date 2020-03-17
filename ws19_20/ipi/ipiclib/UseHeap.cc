#include<vector>
#include<iostream>

#include"Heap.hh"
#include"Zufall.cc"

int main ()
{
  Zufall z(87123);
  Heap<int> h;

  for (int i=0; i<10; i=i+1) {
    int k = z.ziehe_zahl();
    std::cout << k << std::endl;
    h.push(k);
    if (i==5) h.pop();
  }
  std::cout << std::endl;
  while (!h.empty()) {
    std::cout << h.top() << std::endl;
    h.pop();
  }
}
