class Analyzer : public Circuit {
public:
	Analyzer (int m);
	// Konstruktor

	~Analyzer ();
    // Destruktor

	virtual void ChangeInput (State s, int pin);
    // Eingang wechselt zur aktuellen Zeit den Zustand

	virtual void Action ();                  
    // berechne Gatter neu und benachrichtige Draht
    // am Ausgang

	virtual void ConnectInput (Wire& w, int pin); 
    // verdrahte Eingang

	virtual void ConnectOutput (Wire& w, int pin); 
    // verdrahte Ausgang

private:
    int n;           // Anzahl Eingaenge
	Wire** a;        // Die n Eingangsdraehte
    Wire*  b;        // Engang fuer Selbstaktivierung
    Wire*  c;        // Ausgang fuer Selbstaktivierung
	bool actionFlag; // merke ob bereits aktiviert
	Wire w;          // Draht fuer Selbstaktivierung
} ;
