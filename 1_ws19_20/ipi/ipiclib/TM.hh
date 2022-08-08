// Klasse, die eine Turingmaschine realisiert
class TM {
public:
  // Konstruiere Maschine mit Programm
  // und Band
  TM (Programm& p, Band& b);

  // Mache einen Schritt
  void Schritt ();

  // Liefere true falls sich Maschine im 
  // Endzustand befindet
  bool Endzustand ();

private:
  Programm& prog; // Merke Programm
  Band& band;     // Merke Band
  int q;          // Merke akt. Zustand
} ;
