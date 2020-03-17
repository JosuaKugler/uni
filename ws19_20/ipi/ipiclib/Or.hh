class Or : public Circuit {
public:
	Or ();
	// Konstruktor

	~Or ();
    // default destructor ist OK

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
	Wire* a;         // Eingang 1
	Wire* b;         // Eingang 2
	Wire* c;         // Ausgang
	bool actionFlag; // merke ob bereits aktiviert
} ;
