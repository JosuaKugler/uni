class Nand : public Circuit {
public:
  // Konstruktor
  Nand ();

  // default destructor ist OK
  ~Nand ();

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
  Wire* a;         // Eingang 1
  Wire* b;         // Eingang 2
  Wire* c;         // Ausgang
  bool actionFlag; // merke ob bereits aktiviert
} ;
