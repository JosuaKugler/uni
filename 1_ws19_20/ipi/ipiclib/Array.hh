template <class T> class Array {
public:
  typedef T MemberType;  // Merke Grundtyp

  // Iterator fuer die Feld-Klasse
  class Iterator {
  private: 
    T* p; // Iterator ist ein Zeiger ...
    Iterator(T* q) {p=q;}
  public:
    Iterator() {p=0;}
    bool operator!= (Iterator x) {
      return (p!=x.p);
    }
    bool operator== (Iterator x) {
      return (p==x.p);
    }
    Iterator operator++ () {
      p++;
      return *this;
    }
    Iterator operator++ (int) {
      Iterator tmp = *this;
      ++*this;
      return tmp;
    }
    T& operator* () const {return *p;}
    T* operator-> () const {return p;}
    friend class Array<T>;
  } ;

  // Iterator Methoden
  Iterator begin () const {
    return Iterator(p);
  }
  Iterator end () const {
    return Iterator(&(p[n])); // ja, das ist ok!
  }

  // Konstruktion; Destruktion und Zuweisung
  Array(int m) {
    n = m;
    p = new T[n];
  }
  Array (const Array<T>&);
  Array<T>& operator= (const Array<T>&);
  ~Array() {
    delete[] p;
  }

  // Array manipulation
  int size () const {
    return n;
  }
  T& operator[](int i) {
    return p[i];
  }

private:
  int n;  // Anzahl Elemente
  T *p;   // Zeiger auf built-in array
} ;

// Copy-Konstruktor
template <class T>
Array<T>::Array (const Array<T>& a) {
  n = a.n;
  p = new T[n];
  for (int i=0; i<n; i=i+1)
    p[i]=a.p[i];
}

// Zuweisung
template <class T>
Array<T>& Array<T>::operator= (const Array<T>& a) {
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

// Ausgabe
template <class T>
std::ostream& operator<< (std::ostream& s, Array<T>& a) {
  s << "array " << a.size() <<
    " elements = [" << std::endl;
  for (int i=0; i<a.size(); i++)
    s << "    " << i << "  " << a[i] << std::endl;
  s << "]" << std::endl;
  return s;
}
