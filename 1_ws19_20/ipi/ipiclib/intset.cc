// Die Menge wird durch ein IntList realisiert
struct IntSet {
  IntList list;
} ;

// Erzeuge eine leere Menge
IntSet* empty_set ()
{
  IntSet* s = new IntSet;

  empty_list(&s->list);
  return s;
}

// pruefe ob x in Menge ist
bool is_in_set (IntSet* s, int x)
{
  for (IntListElem* p=s->list.first; p!=0; p=p->next)
    if (p->value==x) return true;
  return false;
}

// Fuege Element in Menge ein
void insert_in_set (IntSet* s, int x)
{
  // pruefe ob Element bereits in Liste
  // sonst fuege es ein
  if (!is_in_set(s,x))
    {
      IntListElem* p = new IntListElem;
      p->value = x;
      insert_in_list(&s->list,0,p);
    }
}

// Entferne x aus Menge
void remove_from_set (IntSet* s, int x)
{
  // Hat es ueberhaupt Elemente?
  if (s->list.first==0) return;

  // Teste erstes Element
  if (s->list.first->value==x)
    {
      IntListElem* p=remove_from_list(&s->list,0);
      delete p;
      return;
    }

  // Suche in Liste, teste immer Nachfolger
  // des aktuellen Elementes
  for (IntListElem* p=s->list.first; p->next!=0; p=p->next)
    if (p->next->value==x)
      {
	IntListElem* q=remove_from_list(&s->list,p);
	delete q;
	return;
      }
}

// drucke Liste
void print_set (IntSet* s)
{
  print("(");
  for (IntListElem* p=s->list.first; p!=0; p=p->next)
    print("  ",p->value,0);
  print(")");
}
