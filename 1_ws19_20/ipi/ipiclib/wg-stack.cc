#include "fcpp.hh"

int nennwert (int nr) {// Muenzart -> Muenzwert
  if (nr==1) return 1;	if (nr==2) return 2;
  if (nr==3) return 5; 	if (nr==4) return 10;
  if (nr==5) return 50;
  return 0;
}

struct Arg {        // Stapelelemente
  int betrag;       // das sind die Argumente der
  int muenzarten; };// rekursiven Variante

const int N = 1000; // Stapelgroesse

int wechselgeld2 (int betrag) {
  Arg stapel[N];  // hier ist der Stapel
  int i=0;        // der "stack pointer" 
  int anzahl=0;   // das Ergebnis
  int b,m;        // Hilfsvariablen in Schleife

  stapel[i].betrag = betrag; // initialisiere St.
  stapel[i].muenzarten = 5;  // Startwert
  i = i+1;                   // ein Element mehr

  while (i>0) {   // Solange Stapel nicht leer
    i = i-1;      // lese oberstes Element
    b = stapel[i].betrag;// lese Argumente
    m = stapel[i].muenzarten;

    if ( b==0 )
      anzahl = anzahl+1; // Moeglichkeit gefunden
    else if ( b>0 && m>0 ) {
      if (i>=N) {
        print("Stapel zu klein"); 
        return anzahl;
      }
      stapel[i].betrag = b;      // Betrag b 
      stapel[i].muenzarten = m-1;// mit m-1 Muenzarten
      i = i+1;

      if (i>=N) {print("Stapel zu klein"); return anzahl;}
      stapel[i].betrag = b-nennwert(m);
      stapel[i].muenzarten = m; // mit m Muenzarten
      i = i+1;
    }
  }

  return anzahl; // Stapel ist jetzt leer
}

int main () {
  print(wechselgeld2(300));
}

