#include <iostream>
#include <unistd.h> // needed for usleep
#include <string>
#include <sstream>
#include <fstream>

#include "boolcanvas.hh"

// TODO Implementierung des 2D Bool Array
//      Entweder basierend auf der Leinwandimplementierung der Mandelbrot-Aufgabe
//      oder Ihre eigene
//      Ueberladen Sie ggf. die Operatoren operator<< oder operator>> fuer diese Datenstruktur

// Basisklassen
struct Regel
{
  typedef Canvas Daten;
  virtual void anwenden(Daten &daten) = 0;
};

struct BoundaryCondition
{
  typedef Canvas Daten;
  virtual bool boundary(Daten &daten, int i, int j) = 0;
};

// abgeleitete Klassen durch Vererbung
// Sie koennen auch eine Randbedingung und Game of Life Regel ohne Vererbung implementieren
// Allerdings muss in der Klasse Automat ggf. der Datentyp anpasst werden
class TorusCondition : public BoundaryCondition
{
  // Implementieren Sie hier die Funktion boundary()
  // sodass das Gebiet als doppelt periodisch angenommen wird
};

class AliveCondition : public BoundaryCondition
{
  // Implementieren Sie hier die Funktion boundary()
  // Randbedingung durch rund um das Rechengebiet lebende Zellen
};

class DeadCondition : public BoundaryCondition
{
  // Implementieren Sie hier die Funktion boundary()
  // Randbedingung durch rund um das Rechengebiet tote Zellen
};

class GameOfLifeRules : public Regel
{
public:
  // der Datentyp fuer das 2D Bool Array
  typedef Canvas Daten;

  GameOfLifeRules(BoundaryCondition &bc)
      : _bc(bc)
  {
  }

  // TODO Implementieren Sie hier die Regeln des Game of Life in der Funktion anwenden()

private:
  BoundaryCondition &_bc;
}; // end class GameOfLifeRules

// Ein zellulaerer Automat, der Regeln und Datenstrukturen von aussen bekommt
class Automat
{
public:
  // der Datentyp fuer das 2D Bool Array
  typedef Canvas Daten;

  Automat(Daten &daten, Regel &regel)
      : _daten(daten), _regel(regel)
  {
  }

  // mache n Schritte
  void doSteps(int n = 1)
  {
    for (int i = 0; i < n; ++i)
    {
      // Linux-spezifische Art und Weise den Inhalt der Konsole zu loeschen
      // und den Cursor nach oben links zu setzen.
      std::cout << "\x1B[2J\x1B[H"
                << "Step " << i << std::endl
                << _daten;
      // Das Wiedergeben der Loesung soll immer 10 Sekunden (=1e7 Mikrosekunden)
      // dauern. Sie koennen diesen Wert auch aendern.
      usleep(1.e7 / n);
      _regel.anwenden(_daten);
    }
  }

private:
  Daten &_daten;
  Regel &_regel;
};

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cout << "Usage: ./<progname> <txt-file>" << std::endl;
    return 1;
  }
  std::string raw_data;
  int vertpixels = 0;
  int horpixels = 0;
  int counter = 0;
  while (true)
  {
    std::string c;
    std::cin >> c;
    if (c == " " and counter == 0)
    {
      std::stringstream firstint(raw_data);
      firstint >> vertpixels;
      ++counter;
      raw_data = "";
    }
    else if (c == "\n" and counter == 1)
    {
      std::stringstream secondint(raw_data);
      secondint >> horpixels;
      ++counter;
      raw_data = "";
    }
    raw_data += c;
    if (not std::cin)
    {
      break;
    }
  }

  
  
  // Initialisiere Datenstruktur des 2D Bool Array
  
  // TODO
  // Ueberlegen Sie sich wie Sie einen Startzustand in das 2D Bool Array bekommen
  // Lesen Sie ggf.
  // (1) eine solche Textdatei mittels Filestream ein
  // (2) ueberladen Sie Operatoren operator<< oder operator>>

  // TODO
  // - legen Sie eine Instanz der Randbedingung an
  // - legen Sie eine Instanz des Regelsystems an
  // - Initialisieren Sie den zellulaeren Automaten

  // Experimentieren Sie hier mit Ihrem Automaten

  return 0;
}
