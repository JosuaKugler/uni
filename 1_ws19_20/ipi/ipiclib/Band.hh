// Klasse fuer ein linksseitig begrenztes Band 
// einer Turingmaschine.
// Das Band wird durch eine Zeichenkette aus 
// Elemente des Typs char realisiert
class Band {
public:
  // Initialisiere Band mit s, fuelle Rest
  // mit dem Zeichen init auf.
  // Setze aktuelle Bandposition auf linkes Ende.
  Band (std::string s, char init);

  // Lese Symbol unter dem Lesekopf
  char lese ();

  // Schreibe und gehe links
  void schreibe_links (char symbol);

  // Schreibe und gehe rechts
  void schreibe_rechts (char symbol);

  // Drucke aktuellen Bandinhalt bis zur
  // maximal benutzten Position
  void drucke ();
private:
  enum {N=100000};  // maximal nutzbare Groesse
  char band[N];     // das Band
  int pos;          // aktuelle Position
  int benutzt;      // bisher beschriebener Teil
} ;
