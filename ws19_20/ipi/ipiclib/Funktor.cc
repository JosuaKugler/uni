#include <iostream>

class Function {
public:
  virtual ~Function () {};
  virtual int operator() (int) = 0;
};

class Inkrementierer : public Function {
public:
  Inkrementierer (int n) {inkrement = n;}
  int operator() (int n) {return n+inkrement;}
private:
  int inkrement;
};

void schleife (Function& func) {
  for (int i=1; i<10; i++)
    std::cout << func(i) << " ";
  std::cout << std::endl;
}

class Quadrat : public Function {
public:
  int operator() (int n) {return n*n;}
} ;

int main () {
  Inkrementierer ink(10);
  Quadrat quadrat;
  schleife (ink);
  schleife (quadrat);
}
    
