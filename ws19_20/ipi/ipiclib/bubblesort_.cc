/* ist in namespace std schon enthalten:
   template <class T> void swap (T& a, T&b) {
   T t = a;
   a = b;
   b = t;
   }
*/

template <class C> void bubblesort (C& a) {
  for (int i=a.maxIndex(); i>=a.minIndex(); i=i-1)
    for (int j=a.minIndex(); j<i; j=j+1)
      if (a[j+1]<a[j])
        std::swap(a[j+1], a[j]);
}
