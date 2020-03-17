class Circuit {
public:
  // virtual destructor
  virtual ~Circuit ();                            

  // (F): Eingang wechselt Zustand
  virtual void ChangeInput (State s, int pin) = 0;

  // (C): Ausgang neu berechnen
  virtual void Action () = 0;                  

  // verdrahte Eingang
  virtual void ConnectInput (Wire& w, int pin) = 0; 

  // verdrahte Ausgang
  virtual void ConnectOutput (Wire& w, int pin) = 0; 
} ;

Circuit::~Circuit () {}
