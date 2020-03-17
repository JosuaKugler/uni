#include <iostream>
using namespace std;

class Inkrementierer {
public:
  Inkrementierer (int n) {inkrement = n;}
  int operator() (int n) {return n+inkrement;}
private:
  int inkrement;
};

class Quadrat {
public:
  int operator() (int n) {return n*n;}
} ;

template<class T>
void schleife (T& func) {
  for (int i=1; i<10; i++)
    cout << func(i) << " ";
  cout << endl;
}

int main () {
  Inkrementierer ink(10);
  Quadrat quadrat;
  schleife(ink);
  schleife(quadrat);
}
