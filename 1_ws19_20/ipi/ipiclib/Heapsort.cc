template <class C>
inline void reheap (C& a, int n, int i) {
  while (2*i+1<n)
    {
      int l = 2*i+1;
      int r = l+1;
      int k = ((r<n) && (a[r]>a[l])) ? r : l;
      if (a[k]<=a[i]) break;
      std::swap(a[k], a[i]);
      i = k;
    }
}

template <class C> 
void heapsort (C& a)
{
  // build the heap by reheaping from the rear
  for (int i=a.size()-1; i>=0; i--)
    reheap(a, a.size(), i);
  // build the sorted list by popping the heap 
  for (int i=a.size()-1; i>=0; i--) {
    std::swap(a[0],a[i]);
    reheap(a, i, 0);
  }
}
