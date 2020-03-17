template <class C>
void bubblesort (C& a) {
  for (int i=a.size()-1; i>=0; i--)
    for (int j=0; j<i; j=j+1)
      if (a[j+1]<a[j])
        std::swap(a[j+1], a[j]);
}
