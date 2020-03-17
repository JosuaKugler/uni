template <class C>
int binsearch (C& a, typename C::value_type x)
{   // returns either index (if found) or -1
  int l = 0;
  int r = a.size();
  while (1) {
    int m = (l+r)/2;
    if (m==l)
      return (a[m]==x) ? m : -1;
    if (x<a[m])
      r = m;
    else
      l = m;
  }
}
        
