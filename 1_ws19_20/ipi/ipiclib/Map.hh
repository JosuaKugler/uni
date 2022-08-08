// Existiert schon als std::pair
// template<class Key, class T>
// struct pair {
//     Key first;
//     T second;
// } ;

template<class Key, class T>
class Map : private DLList<pair<Key,T> > {
public :

  T& operator[](const Key& k);

  typedef typename DLList<pair<Key,T> >::Iterator Iterator;
  Iterator begin () const; 
  Iterator end () const;
  Iterator find (const Key& k);
} ;
