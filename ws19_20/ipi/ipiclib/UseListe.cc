#include<iostream>
#include"Liste.hh"

int main () {
  List<int> list;
    
  list.insert(0,17); 
  list.insert(0,34); 
  list.insert(0,26);

  for (List<int>::Link* l=list.first(); 
       l!=0; l=l->next())
    std::cout << l->item << std::endl;
  for (List<int>::Link* l=list.first(); 
       l!=0; l=l->next())
    l->item = 23;
}
