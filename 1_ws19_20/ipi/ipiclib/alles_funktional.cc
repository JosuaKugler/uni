#include "fcpp.hh"
  
int quadrat (int x) {return x*x;}

int absolut (int x) {return cond( x<=0, -x , x);}

int main ()
{
  return print( absolut(-4)*(7*quadrat(3)+8) );
}
