class Clock : public Circuit {
public:
	Clock (int m, State initial);
	// Konstruktor

	~Clock ();
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
	State init;      // erster Zustand
    int n;           // Taktrate
	Wire* a;         // Eingang Selbstaktivierung
    Wire* b;         // Ausgang fuer Selbstaktivierung
    Wire* c;         // Ausgang fuer Taktsignal
	bool actionFlag; // merke ob bereits aktiviert
	Wire w;          // Draht fuer Selbstaktivierung
} ;
