int fak (int n)
{
  int ergebnis=1;
  int zaehler=2;
  
  while (zaehler<=n)
    {
      ergebnis = zaehler*ergebnis;
      zaehler  = zaehler+1;
    }
  return ergebnis;
}
