#include<iostream>
#include<vector>
#include"Bubblesort.cc"
#include"Selectionsort.cc"
#include"Insertionsort.cc"
#include"Mergesort.cc"
#include"Heapsort.cc"
#include"Quicksort.cc"
#include"Zufall.cc"
#include"timestamp.cc"

void initialize (std::vector<int>& a) {
  Zufall z(8267);
  for (int i=0; i<a.size(); ++i)
    a[i] = z.ziehe_zahl();
}

int main ()
{
  int n = 100000;
  std::vector<int> a(n);

  initialize(a);
  time_stamp();
  quicksort(a);
  std::cout << "n=" << n << " quicksort t=" 
	    << time_stamp() << std::endl;  

  initialize(a);
  time_stamp();
  mergesort(a);
  std::cout << "n=" << n << " mergesort t=" 
	    << time_stamp() << std::endl;  

  initialize(a);
  time_stamp();
  heapsort(a);
  std::cout << "n=" << n << " heapsort t=" 
	    << time_stamp() << std::endl;  

  initialize(a);
  time_stamp();
  bubblesort(a);
  std::cout << "n=" << n << " bubblesort t=" 
	    << time_stamp() << std::endl;  

  initialize(a);
  time_stamp();
  insertionsort(a);
  std::cout << "n=" << n << " insertionsort t=" 
	    << time_stamp() << std::endl;  

  initialize(a);
  time_stamp();
  selectionsort(a);
  std::cout << "n=" << n << " selectionsort t=" 
	    << time_stamp() << std::endl;  
}
