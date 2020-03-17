int fak (int n)
{
  int ergebnis=1;
  
  for (int zaehler=2; zaehler<=n; 
       zaehler = zaehler+1)
    ergebnis = zaehler*ergebnis;
  
  return ergebnis;
}
