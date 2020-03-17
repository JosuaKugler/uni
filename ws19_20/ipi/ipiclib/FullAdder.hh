class FullAdder : public Circuit {
public:
	FullAdder ();
	// Konstruktor

	~FullAdder ();
    // destruktor

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
	Wire w1,w2,w3;     // lokale Draehte
	Or A;              // Und Gatter
	HalfAdder ha1,ha2; // Halbaddierer
} ;
