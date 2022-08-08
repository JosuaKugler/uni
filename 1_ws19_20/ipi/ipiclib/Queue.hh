template<class T>
class Queue : public DLList<T> {
public :
  // Default-Konstruktoren + Zuweisung OK
  bool empty () {
    return DLList<T>::empty();
  }
  T front () {
    return *DLList<T>::begin();
  }
  T back () {
    return *DLList<T>::rbegin();
  }
  void push (T t) {
    this->insert(DLList<T>::end(),t);
  }
  void pop () {
    this->erase(DLList<T>::begin());
  }
} ;
