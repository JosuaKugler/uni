template<class T>
class List {
public:
  // Infrastruktur
  List() { _first=0; }
  ~List();

  // Listenelement als nested class
  class Link {
    Link* _next;
  public:
    T item;
    Link (T& t) {item=t;}
    Link* next () {return _next;}
    friend class List<T>;
  };

  Link* first() {return _first;}
  void insert (Link* where, T t);
  void remove (Link* where);

private:
  Link* _first;
  // privater Copy-Konstruktor und Zuweisungs-
  // operator da Defaultvarianten zu fehlerhaftem
  // Verhalten fuehren
  List (const List<T>& l) {};
  List<T>& operator= (const List<T>& l) {};
};

template<class T> List<T>::~List()
{
  Link* p = _first;
  while (p!=0)
    {
      Link* q = p;
      p = p->next();
      delete q;
    }
}

template<class T>
void List<T>::insert (List<T>::Link* where, T t)
{
  Link* ins = new Link(t);
  if (where==0)
    {
      ins->_next = _first;
      _first = ins;
    }
  else
    {
      ins->_next = where->_next;
      where->_next = ins;
    }
}

template<class T>
void List<T>::remove (List<T>::Link* where)
{
  Link* p;
  if (where==0)
    {
      p = _first;
      if (p!=0) _first = p->_next;
    }
  else
    {
      p = where->_next;
      if (p!=0) where->_next = p->_next;
    }
  delete p;
}
