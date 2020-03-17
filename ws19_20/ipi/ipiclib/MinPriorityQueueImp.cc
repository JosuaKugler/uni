template<class T>
bool MinPriorityQueue<T>::empty () {
  return DLList<T>::empty();
}
  
template<class T>
void MinPriorityQueue<T>::push (T t) {
  this->insert(DLList<T>::begin(),t);
}

template<class T>
typename DLList<T>::Iterator 
MinPriorityQueue<T>::find_minimum () {
  typename DLList<T>::Iterator min=DLList<T>::begin();
  for (typename DLList<T>::Iterator i=DLList<T>::begin(); 
       i!=DLList<T>::end(); i++)
    if (*i<*min) min=i;
  return min;
}

template<class T>
inline void MinPriorityQueue<T>::pop () {
  this->erase(find_minimum());
}

template<class T>
inline T MinPriorityQueue<T>::top () {
  return *find_minimum();
}
