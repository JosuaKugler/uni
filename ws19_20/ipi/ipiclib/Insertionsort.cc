template <class C> 
void insertionsort (C& a) {
  for (int i=1; i<a.size(); i=i+1) {
    // i Elemente sind sortiert
    int j=i;
    while (j>0 && a[j-1]>a[j]) {
      std::swap(a[j], a[j-1]);
      j=j-1;
    }
  }
}
