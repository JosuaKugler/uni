#include "fcpp.hh"

int main ()
{
  char name[32] = "Peter Bastian";
  
  for (int i=0; name[i]!=0; i=i+1)
    print(name[i]);     // einzelne Zeichen
  print(name);          // ganze Zeichenkette
}
