#include "fcpp.hh"

int main ()
{
    for (int i=32; i<=127; i=i+1)
      print(i,(char) i,0);
}
