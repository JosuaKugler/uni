#include "fcpp.hh"       // fuer print
#include "Zufall.cc"     // Code fuer die beiden
#include "Experiment.cc" // Klassen hereinziehen

double montecarlo (Experiment& e, int N)
{
  int erfolgreich=0;

  for (int i=0; i<N; i=i+1)
    erfolgreich = erfolgreich+e.durchfuehren();

  return ((double)erfolgreich)/((double)N);
}

int main (int argc, char** argv)
{
  Zufall z(93267); // ein Zufallsgenerator
  Experiment e(z); // ein Experiment

  print(sqrt(6.0/montecarlo(e,readarg_int(argc,argv,1))));
}
