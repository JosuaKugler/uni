class Fork : public Circuit {
public:
  // Konstruktor
  Fork ();

  // default destructor ist OK
  ~Fork ();

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
  Wire* a;         // Eingang
  Wire* b;         // Ausgang 1
  Wire* c;         // Ausgang 2
} ;
