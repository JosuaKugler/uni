class HalfAdder : public Circuit {
public:
  // Konstruktor
  HalfAdder ();

  // destruktor
  ~HalfAdder ();

  // Eingang wechselt zur aktuellen Zeit den Zustand
  virtual void ChangeInput (State s, int pin);

  // berechne Gatter neu und benachrichtige Draht
  // am Ausgang
  virtual void Action ();                  

  // verdrahte Eingang
  virtual void ConnectInput (Wire& w, int pin); 

  // verdrahte Ausgang
  virtual void ConnectOutput (Wire& w, int pin); 

private:
  Wire w1,w2,w3,w4,w5,w6,w7; // lokale Draehte
  And A;           // Und Gatter
  Nor N1,N2;       // sowie zwei Nor Gatter
  Fork F1,F2,F3;   // und drei Verzweigungen
} ;
