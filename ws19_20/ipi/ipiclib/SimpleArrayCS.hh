template <class T, int m>
class SimpleArrayCS { 
public:
	SimpleArrayCS (T f);
    // Erzeuge ein neues Feld mit m Elementen, I=[0,m-1]

	// Copy-Konstruktor, Zuweisung, Destruktor: Default ist OK!

	T& operator[](int i);
	// Indizierter Zugriff auf Feldelemente
	// keine Ueberpruefung ob Index erlaubt

	int numIndices ();
	// Anzahl der Indizes in der Indexmenge

	int minIndex ();
	// kleinster Index

	int maxIndex ();
	// größter Index

	bool isMember (int i);
	// Ist der Index in der Indexmenge?

private:
	T p[m]; // built-in array fester Groesse
} ;
