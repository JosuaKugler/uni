#include </home/josua/uni/ipi/ipiclib/fcpp.hh>

// Ein Listenelement
struct IntListElem {
  IntListElem* next;  // Zeiger auf naechstes Element
  int value;          // Daten zu diesem Element  
} ;

// Eine Liste
struct IntStruct {
  int count;          // Anzahl Elemente in der Liste
  IntListElem* first; // Zeiger auf erstes Element der Liste
} ;


// Initialisiere eine Listenstruktur
void empty_list (IntStruct* l)
{
  l->first = 0;   // 0 ist keine gueltige Adresse: Liste ist leer
  l->count = 0;
}

// Fuege ein Element nach einem gegebenem ein
void insert_in_list(IntStruct* list,IntListElem* where,IntListElem* ins)
{
  if (where==0) // fuege am Anfang ein
    {
      ins->next = list->first;
      list->first = ins;
      ++list->count;
    }
  else         // fuege nach where ein
    {
      ins->next = where->next;
      where->next = ins;
      ++list->count;
    }
}

// Entferne ein Element nach einem gegebenem
// Liefere das entfernte Element zurueck
IntListElem* remove_from_list (IntStruct* list, IntListElem* where)
{
  IntListElem* p;  // das entfernte Element

  // where==0 dann entferne erstes Element
  if (where==0) 
    {
      p = list->first;
      if (p!=0)
	{
	  list->first = p->next;
	  list->count = list->count - 1;
	}
      return p;
    }

  // entferne Element nach where
  p = where->next;
  if (p!=0)
    {
      where->next = p->next;
      list->count = list->count - 1;
    }
  return p;
}

class IntList
{
public:
// Konstruktor, erzeugt eine leere Liste
IntList();
//Copy-Konstruktor
IntList( IntList& oldlist);
//Zuweisung
IntList& operator=( IntList& oldlist);
// Destruktor, loescht gesamten Listeninhalt
~IntList();
// Gibt Anzahl der Elemente zurueck
int getCount();
// Gibt zurueck, ob die Liste leer ist
bool isEmpty();
// Gibt die Liste aus
void print();
// Fuegt die Zahl 'element' an der (beliebigen) Position 'position' ein
void insert(int element, int position);
//insert ganz hinten
void insert(int element);
// Loescht das Element an der Position 'position'
void remove(int position);
// Gibt den Wert des Elements an der Position 'position' zurueck
int getElement(int position);
private:
// ... (hier folgen private Member der Klasse)
IntStruct liste;
IntListElem* elementpointer(int position);
};


IntList::IntList() {empty_list(&liste);}
//Copy-Konstruktor
IntList::IntList( IntList& oldlist )
{
    empty_list(&liste);
    for (int i = 0; i < oldlist.getCount(); ++i)
    {
        this->insert(oldlist.getElement(i));
    }
    //std::cout << "hello" << std::endl;
}
//Zuweisungsoperator
IntList& IntList::operator=( IntList& oldlist)
{
    if (this != &oldlist)
    {
        empty_list(&liste);
        for (int i = 0; i < oldlist.getCount(); ++i)
        {
            this->insert(oldlist.getElement(i));
        }
    }
}
//Destruktor
IntList::~IntList() {empty_list(&liste);}
int IntList::getCount() {return liste.count;}
bool IntList::isEmpty() 
{
    if (liste.count == 0) 
    {
        return true;
    } 
    else  
    {
        return false;
    }
}
void IntList::print()
{
    std::cout << "[";
    for (IntListElem* p = liste.first; p != 0; p = p->next)
    {
        std::cout << p->value <<  " ";
    }
    std::cout << "]"<<std::endl;
}
void IntList::insert(int element, int position)
{
    IntListElem* where = elementpointer(position);
    IntListElem* ins = new IntListElem;
    ins->value = element;
    insert_in_list(&liste, where, ins);   
}
void IntList::insert(int element)
{
    IntListElem* where = elementpointer(liste.count);
    IntListElem* ins = new IntListElem;
    ins->value = element;
    insert_in_list(&liste, where, ins);
}
void IntList::remove(int position)
{
    IntListElem* where = elementpointer(position + 1);
    remove_from_list(&liste, where);
}

int IntList::getElement(int position)
{
    IntListElem* pointer = elementpointer(position);
    return pointer->value;
}
IntListElem* IntList::elementpointer(int position)
{
    IntListElem* where = liste.first;
    int counter = 0;
    while (counter < position)
    {
        where = where->next;
        counter = counter + 1;
        //std::cout << where->value <<  " ";
    }
    return where;
}


int main()
{
IntList list;
list.insert(30);
list.insert(20);
list.insert(10);
list.print();
list.remove(2);
list.print();
list.insert(30,2);
list.print();
list.insert(40,3);
list.print();
IntList copy(list);
copy.print();
copy.remove(0);
copy.print();
list.print();
copy.print();
return 0; 
}