template <class T, int m>
inline SimpleArrayCS<T,m>::SimpleArrayCS (T v)
{
  for (int i=0; i<m; i=i+1) p[i]=v;
}

template <class T, int m>
inline T& SimpleArrayCS<T,m>::operator[] (int i)
{
  return p[i];
}

template <class T, int m>
inline int SimpleArrayCS<T,m>::numIndices () { return m; }

template <class T, int m>
inline int SimpleArrayCS<T,m>::minIndex () { return 0; }

template <class T, int m>
inline int SimpleArrayCS<T,m>::maxIndex () { return m-1; }

template <class T, int m>
inline bool SimpleArrayCS<T,m>::isMember (int i)
{
  if (i>=0 && i<m) return true;
  else return false;
}

template <class T, int m>
std::ostream& operator<< (std::ostream& s, SimpleArrayCS<T,m>& a)
{
  for (int i=a.minIndex(); i<=a.maxIndex(); i=i+1)
    s << i << " " << a[i] << std::endl;
  return s;
}
