template<class T>
class MinPriorityQueue : public DLList<T> {
private:
  typename DLList<T>::Iterator find_minimum();
public :
  // Default-Konstruktoren + Zuweisung OK
  bool empty ();
  void push (T t);  // Einfuegen
  void pop ();      // Entferne kleinstes
  T top ();         // Inspiziere kleinstes
} ;
