template<class T>
class Stack : private DLList<T> {
public :
  // Default-Konstruktoren + Zuweisung OK

  bool empty () {return DLList<T>::empty();}
  void push (T t) {
    this->insert(DLList<T>::begin(),t);
  }
  T top () {return *DLList<T>::begin();}
  void pop () {this->erase(DLList<T>::begin());}
} ;
