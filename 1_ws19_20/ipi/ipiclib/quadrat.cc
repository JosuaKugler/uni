#include "fcpp.hh"
  
int quadrat (int x)
{
  return x*x;
}

int main ()
{
  return print( quadrat(3)+quadrat(4+4) );
}
