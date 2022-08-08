// Konstruktor fuer leeres Programm
Programm::Programm ()
{
  zeilen = 0; // noch keine gueltige Zeile
  fertig = false;
}

// Fuege eine Zeile in die Zustandsuebrgangstabelle hinzu
void Programm::zeile (int q_ein, char s_ein, char s_aus, R richt, int q_aus)
{
  if (fertig) {
    print("Programm war schon abgeschlossen!");
    return;
  }
  Qaktuell[zeilen] = q_ein;
  eingabe[zeilen] = s_ein;
  ausgabe[zeilen] = s_aus;
  richtung[zeilen] = richt;
  Qfolge[zeilen] = q_aus;
  zeilen = zeilen+1;
}

// Definiere letzte Zeile in der Zustandsuebergangstabelle
void Programm::zeile (int endzustand)
{
  if (fertig) {
    print("Programm war schon abgeschlossen!");
    return;
  }
  Qaktuell[zeilen] = endzustand;
  zeilen = zeilen+1;
  fertig = true;
  print("Programm mit ",zeilen," Zeilen definiert",0);
  print("Anfangszustand ",Anfangszustand(),0);
  print("Endzustand ",Endzustand(),0);
}

// Ermittle zu schreibendes Zeichen
char Programm::Ausgabe (int q, char symbol)
{
  // wurde Zeile als letztes benutzt ?
  if ( letztesQ==q && letzteEingabe==symbol )
    return ausgabe[letzteZeile];
  // suche Zeile im Programm
  if (FindeZeile(q,symbol))
    return ausgabe[letzteZeile];
  // Fehler: es gibt keine solche Zeile
  print(q," , ",symbol,0);
  print(" nicht definiert!"); 
  return 0;
}

// Ermittle Richtung
Programm::R Programm::Richtung (int q, char symbol)
{
  // wurde Zeile als letztes benutzt ?
  if ( letztesQ==q && letzteEingabe==symbol )
    return richtung[letzteZeile];
  // suche Zeile im Programm
  if (FindeZeile(q,symbol))
    return richtung[letzteZeile];
  // Fehler: es gibt keine solche Zeile
  print(q," , ",symbol,0);
  print(" nicht definiert!"); 
  return links;
}

// Ermittle Folgezustand
int Programm::Folgezustand (int q, char symbol)
{
  // wurde Zeile als letztes benutzt ?
  if ( letztesQ==q && letzteEingabe==symbol )
    return Qfolge[letzteZeile];
  // suche Zeile im Programm
  if (FindeZeile(q,symbol))
    return Qfolge[letzteZeile];
  // Fehler: es gibt keine solche Zeile
  print(q," , ",symbol,0);
  print(" nicht definiert!"); 
  return -1;
}

// Gebe Anfangszustand zurueck
int Programm::Anfangszustand ()
{
  return Qaktuell[0];
}

// Gebe Endzustand zurueck
int Programm::Endzustand ()
{
  return Qaktuell[zeilen-1];
}

// Finde Zeile in der Zustandsuebergangstabelle zu gegebenem
// Zustand und Symbol. Merke Eingabe und Zeilennummer damit
// bei wiederholtem Zugriff nicht gesucht werden muss. 
bool Programm::FindeZeile (int q, char symbol)
{
  for (int i=0; i<zeilen; i=i+1)
    if ( Qaktuell[i]==q && eingabe[i]==symbol )
      {
	letzteZeile = i;
	letztesQ = Qaktuell[letzteZeile];
	letzteEingabe = eingabe[letzteZeile];
	return true;
      }
  return false;
}















