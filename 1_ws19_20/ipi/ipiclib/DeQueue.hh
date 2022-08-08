template<class T>
class DeQueue : private DLList<T> {
public :
  // Default-Konstruktoren + Zuweisung ok
  bool empty ();
  void push_front (T t);
  void push_back (T t);
  T pop_front ();
  T pop_back ();
  T front ();
  T back ();
} ;
