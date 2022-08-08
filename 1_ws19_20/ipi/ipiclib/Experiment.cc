class Experiment {
public: 
  Experiment (Zufall& z); // Konstruktor
  int durchfuehren ();    // einmal ausfuehren
private:
  Zufall& zg; // Merke Zufallsgenerator
  unsigned int ggT (unsigned int a, 
                    unsigned int b);
} ;
  
Experiment::Experiment (Zufall& z) : zg(z) {}
  
unsigned int Experiment::ggT (unsigned int a, unsigned int b)
{
  if (b==0) return a;
  else      return ggT(b,a%b);
}
  
int Experiment::durchfuehren ()
{
  unsigned int x1 = zg.ziehe_zahl();
  unsigned int x2 = zg.ziehe_zahl();
  if (ggT(x1,x2)==1)
    return 1;
  else
    return 0;
}
