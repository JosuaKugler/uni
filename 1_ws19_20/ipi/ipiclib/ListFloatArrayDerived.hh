class ListFloatArray :
    public FloatArray {     // Ableitung
public:
	// Konstruktoren
	ListFloatArray ();      // leeres Feld

	// Destruktor
	~ListFloatArray();      // ersetzt ~FloatArray !!

	// Indizierung
	virtual float& operator[](int i);

	// allgemeine Indexmenge
	virtual int numIndices (); 
	virtual int minIndex ();
	virtual int maxIndex ();
	virtual bool isMember (int i);

private:
	// lokal in der Klasse benutzte Datenstruktur
	struct FloatListElem {
		struct FloatListElem *next; // naechstes Element
		int index;                  // der Index 
		float value;                // der Wert
	};

	int n;              // Anzahl Elemente
	FloatListElem *p;   // einfach verkettete Liste

	FloatListElem* insert (int i, float v); // Fuege in Liste ein
	FloatListElem* find (int i);  // finde Index 
} ;
