#include "fcpp.hh"       // fuer print

class Inkrementierer {
public:
    Inkrementierer (int n) {inkrement = n;}
    int eval (int n) {return n+inkrement;}
private:
    int inkrement;
};

void schleife (Inkrementierer &ink) {
    for (int i=1; i<10; i++)
      print(ink.eval(i));
}

int main () {
    Inkrementierer ink(10);
    schleife (ink);
}
    
