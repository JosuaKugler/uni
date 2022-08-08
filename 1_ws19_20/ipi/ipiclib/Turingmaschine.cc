#include "fcpp.hh" // fuer print

#include"Band.hh"  // Inkludiere Quelldateien
#include"Band.cc"
#include"Programm.hh"
#include"Programm.cc"
#include"TM.hh"
#include"TM.cc"

int main (int argc, char *argv[])
{
  // Initialisiere ein Band
  Band b("1111",'0');
  b.drucke();

  // Initialisiere ein Programm
  Programm p;
  p.zeile(1,'1','X',Programm::rechts,2);
  p.zeile(2,'1','1',Programm::rechts,2);
  p.zeile(2,'0','Y',Programm::links,3);
  p.zeile(3,'1','1',Programm::links,3);
  p.zeile(3,'X','1',Programm::rechts,4);
  p.zeile(4,'Y','1',Programm::rechts,8);
  p.zeile(4,'1','X',Programm::rechts,5);
  p.zeile(5,'1','1',Programm::rechts,5);
  p.zeile(5,'Y','Y',Programm::rechts,6);
  p.zeile(6,'1','1',Programm::rechts,6);
  p.zeile(6,'0','1',Programm::links,7);
  p.zeile(7,'1','1',Programm::links,7);
  p.zeile(7,'Y','Y',Programm::links,3);
  p.zeile(8);

  // Baue eine Turingmaschine
  TM tm(p,b);

  // Simuliere Turingmaschine
  while (!tm.Endzustand()) { // Solange nicht Endzustand
      tm.Schritt() ;         // mache einen Schritt
      b.drucke();            // und drucke Band
    }

  return 0;                  // fertig.
}
