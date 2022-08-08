template <class C> 
int qs_partition (C& a, int l, int r, int q) {
  std::swap(a[q],a[r]);
  q=r;      // Pivot ist jetzt ganz rechts
  int i=l-1, j=r; 

  while (i<j) {
    i=i+1; while (i<j && a[i]<=a[q]) i=i+1;
    j=j-1; while (i<j && a[j]>=a[q]) j=j-1;
    if (i<j)
      std::swap(a[i],a[j]);
    else
      std::swap(a[i],a[q]);
  }
  return i; // endgueltige Position des Pivot
}

template <class C> 
void qs_rec (C& a, int l, int r) {
  if (l<r) { 
    int i=qs_partition(a,l,r,r);
    qs_rec(a,l,i-1);
    qs_rec(a,i+1,r);
  }
}

template <class C> 
void quicksort (C& a) {
  qs_rec(a,0,a.size()-1);
}
