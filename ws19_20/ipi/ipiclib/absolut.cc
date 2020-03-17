#include "fcpp.hh"
  
int absolut (int x)
{
  return cond( x<=0, -x , x); 
}

int main ()
{
  return print( absolut(-3) );
}
