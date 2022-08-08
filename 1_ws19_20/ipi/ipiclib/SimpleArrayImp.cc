// Destruktor
template <class T>
SimpleArray<T>::~SimpleArray () { 
  delete[] p; 
}

// Konstruktor
template <class T>
SimpleArray<T>::SimpleArray (int s, T v) 
{
  n = s;
  p = new T[n];
  for (int i=0; i<n; i=i+1) p[i]=v;
}

// Copy-Konstruktor
template <class T>
SimpleArray<T>::SimpleArray (const 
			     SimpleArray<T>& a) {
  n = a.n;
  p = new T[n];
  for (int i=0; i<n; i=i+1)
    p[i]=a.p[i];
}

// Zuweisungsoperator
template <class T>
SimpleArray<T>& SimpleArray<T>::operator= 
  (const SimpleArray<T>& a)
{
  if (&a!=this) {
    if (n!=a.n) {
      delete[] p;
      n = a.n;
      p = new T[n];
    }
    for (int i=0; i<n; i=i+1) p[i]=a.p[i];
  }
  return *this;
}

template <class T>
inline T& SimpleArray<T>::operator[] (int i) 
{ 
  return p[i];
}

template <class T>
inline int SimpleArray<T>::numIndices () 
{ 
  return n;
}

template <class T>
inline int SimpleArray<T>::minIndex () 
{ 
  return 0; 
}

template <class T>
inline int SimpleArray<T>::maxIndex () 
{ 
  return n-1; 
}

template <class T>
inline bool SimpleArray<T>::isMember (int i) 
{
  return (i>=0 && i<n);
}

template <class T>
std::ostream& operator<< (std::ostream& s, 
		     SimpleArray<T>& a) 
{
  s << "#( ";
  for (int i=a.minIndex(); i<=a.maxIndex(); i=i+1)
    s << a[i] << " ";
  s << ")" << std::endl;
  return s;
}
