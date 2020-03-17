template <class T>
class SimpleArray { 
public:
  SimpleArray (int s, T f);
  SimpleArray (const SimpleArray<T>&);
  SimpleArray<T>& operator= 
    (const SimpleArray<T>&);
  ~SimpleArray();

  T& operator[](int i);
  int numIndices ();
  int minIndex ();
  int maxIndex ();
  bool isMember (int i);

private:
  int n;  // Anzahl Elemente
  T *p;   // Zeiger auf built-in array
} ;
