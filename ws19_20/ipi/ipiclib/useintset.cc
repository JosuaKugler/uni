#include "fcpp.hh"
#include "intlist.cc"
#include "intset.cc"

int main ()
{
  IntSet* s = empty_set();

  print_set(s);

  for (int i=1; i<12; i=i+1)
    insert_in_set(s,i);

  print_set(s);

  for (int i=2; i<30; i=i+2)
    remove_from_set(s,i);

  print_set(s);
}
