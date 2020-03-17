class ListFloatArray :
  public FloatArray {     // Ableitung
public:
  ListFloatArray ();      // leeres Feld
    
  ~ListFloatArray();      // ersetzt ~FloatArray

  virtual float& operator[](int i);
  virtual int numIndices (); 
  virtual int minIndex ();
  virtual int maxIndex ();
  virtual bool isMember (int i);
private:
  struct FloatListElem { // lokale Struktur
    FloatListElem *next;
    int index;
    float value;
  };
  FloatListElem* insert (int i, float v);
  FloatListElem* find (int i);

  int n;           // Anzahl Elemente
  FloatListElem *p;// Listenanfang
} ;

// private Hilfsfunktionen
ListFloatArray::FloatListElem*
ListFloatArray::insert (int i, float v)
{
  FloatListElem* q = new FloatListElem; 

  q->index = i;
  q->value = v;
  q->next = p;
  p = q;
  n = n+1;
  return q;
}

ListFloatArray::FloatListElem* 
ListFloatArray::find (int i)
{
  for (FloatListElem* q=p; q!=0; q = q->next)
    if (q->index==i)
      return q;
  return 0;
}

// Konstruktor
ListFloatArray::ListFloatArray ()
{
  n = 0; // alles leer
  p = 0;
}

// Destruktor
ListFloatArray::~ListFloatArray ()
{
  FloatListElem* q;

  while (p!=0)
    {
      q = p;       // q ist erstes
      p = q->next; // entferne q aus Liste
      delete q;
    }
}

float& ListFloatArray::operator[] (int i)
{
  FloatListElem* r=find(i);
  if (r==0)
    r=insert(i,0.0); // index einfuegen
  return r->value;
}

int ListFloatArray::numIndices ()
{
  return n;
}

int ListFloatArray::minIndex ()
{
  if (p==0) return 0;
  int min=p->index;   
  for (FloatListElem* q=p->next; 
       q!=0; q = q->next)
    if (q->index<min) min=q->index;
  return min;
}

int ListFloatArray::maxIndex ()
{
  if (p==0) return 0;
  int max=p->index;   
  for (FloatListElem* q=p->next; 
       q!=0; q = q->next)
    if (q->index>max) max=q->index;
  return max;
}

bool ListFloatArray::isMember (int i) {
  return (find(i)!=0);
}
