template<class T>
typename Set<T>::Iterator Set<T>::begin() {
  return DLList<T>::begin();
}

template<class T>
typename Set<T>::Iterator Set<T>::end() {
  return DLList<T>::end();
}

template<class T>
bool Set<T>::empty () {
  return DLList<T>::empty();
}
  
template<class T>
inline bool Set<T>::member (T t) {
  return find(t)!=DLList<T>::end();
}

template<class T>
inline void Set<T>::insert (T t)
{
  if (!member(t))
    DLList<T>::insert(DLList<T>::begin(),t);
}

template<class T>
inline void Set<T>::remove (T t)
{
  typename DLList<T>::Iterator i = find(t);
  if (i!=DLList<T>::end())
    erase(i);
}
