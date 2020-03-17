class Adder4Bit : public Circuit {
public:
	Adder4Bit ();
	// Konstruktor

	~Adder4Bit ();
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
	Wire w0,w1,w2;             // lokale Draehte
	FullAdder fa0,fa1,fa2,fa3; // Volladdierer
} ;
