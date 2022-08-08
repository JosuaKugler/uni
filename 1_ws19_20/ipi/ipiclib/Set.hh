template<class T>
class Set : private DLList<T> {
public :
  // Default-Konstruktoren + Zuweisung OK

  typedef typename DLList<T>::Iterator Iterator;
  Iterator begin();
  Iterator end();
    
  bool empty ();
  bool member (T t);
  void insert (T t);
  void remove (T t);
  // union, intersection, ... ?
} ;
