template<class T>
class DLList {

  // das interne Listenelement
  struct Element {
    Element* next;
    Element* prev;
    T item;
    Element (T &t) {
      item = t;
      next = prev = 0;
    }
  };

public:
  typedef T MemberType;  // Merke Grundtyp

  // der iterator kapselt Zeiger auf Listenelement
  class Iterator {
  private:
    Element* p;
  public:
    Iterator () { p=0; }
    Iterator (Element* q) { p=q; }
    bool operator!= (Iterator x) { 
      return p!=x.p; 
    }
    bool operator== (Iterator x) { 
      return p==x.p; 
    }
    Iterator operator++ () { // prefix
      p=p->next;
      return *this;
    }
    Iterator operator++ (int) { // postfix
      Iterator tmp = *this;
      p=p->next;
      return tmp;
    }
    Iterator operator-- () { // prefix
      p=p->prev;
      return *this;
    }
    Iterator operator-- (int) { // postfix
      Iterator tmp = *this;
      p=p->prev;
      return tmp;
    }
    T& operator* () { return p->item; }
    T* operator-> () { return &(p->item); }
    friend class DLList<T>; // Liste man. p
  } ;

  // Iteratoren 
  Iterator begin () const {return head;}
  Iterator end () const {return Iterator();}
  Iterator rbegin () const {return tail;}
  Iterator rend () const {return Iterator();}

  // Konstruktion, Destruktion, Zuweisung
  DLList ();
  DLList (const DLList<T>& list);
  DLList<T>& operator= (const DLList<T>&);
  ~DLList();

  // Listenmanipulation
  Iterator insert (Iterator i, T t);// einf. vor i
  void erase (Iterator i);
  void append (const DLList<T>& l);
  void clear ();
  bool empty () const;
  int size () const;
  Iterator find (T t) const;

private:
  Iterator head;    // erstes Element der Liste
  Iterator tail;    // letztes Element der Liste
} ;


// Insertion
template<class T>
typename DLList<T>::Iterator
DLList<T>::insert (Iterator i, T t)
{
  Element* e = new Element(t);
  if (empty())
    {
      assert(i.p==0);
      head.p = tail.p = e;
    }
  else 
    {
      e->next = i.p;
      if (i.p!=0)
        {   // insert before i
          e->prev = i.p->prev;
          i.p->prev = e;
          if (head==i)
            head.p=e;
        }
      else
        {   // insert at end
          e->prev = tail.p;
          tail.p->next = e;
          tail.p = e;
        }
    }
  return Iterator(e);
}

template<class T>       
void DLList<T>::erase (Iterator i)
{
  if (i.p==0) return;
  
  if (i.p->next!=0)
    i.p->next->prev = i.p->prev;
  if (i.p->prev!=0)
    i.p->prev->next = i.p->next;
  
  if (head==i) head.p=i.p->next;
  if (tail==i) tail.p=i.p->prev;
  
  delete i.p;
}
  
template<class T>
void DLList<T>::append (const DLList<T>& l) {
  for (Iterator i=l.begin(); i!=l.end(); i++)
    insert(end(),*i);
}

template<class T>
bool DLList<T>::empty () const {
  return begin()==end();
}

template<class T>
void DLList<T>::clear () {
  while (!empty())
    erase(begin());
}

// Constructors
template<class T> DLList<T>::DLList () {}

template<class T>       
DLList<T>::DLList (const DLList<T>& list) {
  append(list);
}

// Assignment
template<class T>
DLList<T>&
DLList<T>::operator= (const DLList<T>& l) {
  if (this!=&l) {
    clear();
    append(l);
  }
  return *this;
}
    
// Destructor
template<class T> DLList<T>::~DLList() { clear(); }

// Size method
template<class T> int DLList<T>::size () const {
  int count = 0;
  for (Iterator i=begin(); i!=end(); i++)
    count++;
  return count;
}

template<class T>
typename DLList<T>::Iterator DLList<T>::find (T t) const {
  DLList<T>::Iterator i = begin();
  while (i!=end())
    {
      if (*i==t) break;
      i++;
    }
  return i;
}

template <class T>
std::ostream& operator<< (std::ostream& s, DLList<T>& a) {
  s << "(";
  for (typename DLList<T>::Iterator i=a.begin();
       i!=a.end(); i++)
    {
      if (i!=a.begin()) s << " ";
      s << *i;
    }
  s << ")" << std::endl;
  return s;
}
