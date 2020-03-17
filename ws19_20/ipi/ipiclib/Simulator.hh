// Simulator, Singleton
class Simulator {
public:
  // Konstruktor
  Simulator ();

  // aktuelle Zeit auslesen
  int GetTime ();

  // (B): Draht w wird zur Zeit t in Zustand s wechseln
  void StoreWireEvent (Wire& w, int t, State s); 

  // (D): Baustein c soll zur aktuellen Zeit neu berechnet werden
  void StoreCircuitEvent (Circuit& c);

  // Starte Simulation bei Zeit 0
  void Simulate (int end);

private:
  struct WireEvent { // Eine lokale Struktur
    WireEvent ();  // fuer Ereignis "Zustandswechsel"
    WireEvent (Wire& W, int T, State S);
    Wire* w;
    int t;
    State s;
    bool operator< (WireEvent we);
    void print (std::ostream& stm) {stm << "(WE: " << t << " " << w << " " << s << std::endl; }
  } ;

  int time;
  MinPriorityQueue<WireEvent> pq; // Fuer (B)-Ereignisse
  Queue<Circuit*> q;              // Fuer (D)-Ereignisse
} ;

// Globale Variable vom Typ Simulator (Singleton).
// Wird von allen Bausteinen und Draehten benutzt!
Simulator Sim;
