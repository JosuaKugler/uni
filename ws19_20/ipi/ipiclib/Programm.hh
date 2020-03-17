// Eine Klasse, die das Programm einer
// Turingmaschine realisiert.
// Zustaende sind vom Typ int
// Bandalphabet ist der Typ char
// Anfangszustand ist Zustand in der ersten Zeile
// Endzustand ist Zustand in der letzten Zeile
class Programm {
public:
  // Symbole fuer links/rechts
  enum R {links,rechts};  
      
  // Erzeuge leeres Programm
  Programm ();

  // definiere Zustandsuebergaenge
  // Mit Angabe des Endzustandes ist die 
  // Programmierphase beendet
  void zeile (int q_ein, char s_ein, 
              char s_aus, R richt, int q_aus);
  void zeile (int endzustand);

  // lese Zustandsuebergang in Abhaengigkeit
  // von akt. Zustand und gelesenem Symbol
  char Ausgabe (int zustand, char symbol);
  R Richtung (int zustand, char symbol);
  int Folgezustand (int zustand, char symbol);
  
  // Welcher Zustand ist Anfangszustand
  int Anfangszustand ();

  // Welcher Zustand ist Endzustand
  int Endzustand ();
    
private:
  // Finde die Zeile zu geg. Zustand/Symbol
  // Liefere true, falls so eine Zeile gefunden
  // wird, sonst false
  bool FindeZeile(int zustand, char symbol);

  enum {N=1000};   // maximale Anzahl Uebergaenge
  int zeilen;      // Anzahl Zeilen in Tabelle 
  bool fertig;     // Programmierphase beendet
  int Qaktuell[N]; // Eingabezustand
  char eingabe[N]; // Eingabesymbol
  char ausgabe[N]; // Ausgabesymbol
  R richtung[N];   // Ausgaberichtung
  int Qfolge[N];   // Folgezustand
  int letztesQ;    // Merke Eingabe und Zeilen-
  int letzteEingabe;// nummer des letzten Zu-
  int letzteZeile; // griffes.
} ;
