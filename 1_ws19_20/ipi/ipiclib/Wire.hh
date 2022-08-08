// moegliche Zustaende
enum State {low, high, unknown};

class Wire {
public:
  // Draht im Zustand unknown erzeugen
  Wire ();

  // aktuellen Zustand auslesen
  State GetState ();

  // (E): Zur Zeit t soll Zustand s werden 
  void ChangeState (int t, State s);    

  // (A): wechsle jetzt in neuen Zustand
  void Action (State s);

  // Eingang des Drahtes an Ausgang i des Bausteins c
  // anschliessen
  void ConnectInput (Circuit& cir, int i);

  // Ausgang des Drahtes an Eingang i des Bausteins c
  // anschliessen
  void ConnectOutput (Circuit& cir, int i);

private:
  State q;      // der Zustand
  Circuit* c;   // Baustein am Ausgang des Drahtes
  int pin;      // pin des Bausteins
} ;
