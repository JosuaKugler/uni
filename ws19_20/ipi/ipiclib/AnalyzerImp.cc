Analyzer::Analyzer (int m)
{
  n = m;                              // Merke Groesse, Eingang n
  a = new Wire*[n];                   // n Zeiger auf Wires
  for (int i=0; i<n; i=i+1) a[i] = 0; // nix angeschlossen
  b = c = 0;                          // nix angeschlossen
  w.ConnectInput(*this,0);           // Ich -> Draht
  w.ConnectOutput(*this,n);          // Draht->Ich
  actionFlag=true;                   // nix aktiviert
  Sim.StoreCircuitEvent(*this);      // Starte Auswertung
}

Analyzer::~Analyzer()
{
  delete[] a;
}

void Analyzer::ChangeInput (State s, int pin)
{
  // Sorge dafuer, dass Gatter neu berechnet wird, wenn
  // alle Zustaende der Eingaenge (Draehte) festliegen
  if (!actionFlag)
    {
      Sim.StoreCircuitEvent(*this);
      actionFlag=true;
    }
}

void Analyzer::Action ()
{
  // Lese Eingangssignale
  std::cout.width(10);
  std::cout << Sim.GetTime();
  for (int i=n-1; i>=0; i=i-1)
    if (a[i]!=0) 
      {
	if (a[i]->GetState()==low)     std::cout << "  0";
	if (a[i]->GetState()==high)    std::cout << "  1";
	if (a[i]->GetState()==unknown) std::cout << "  U";
      }
    else std::cout << "   ";
  std::cout << std::endl;

  // Selbstaktivierung im naechsten Zeitschritt
  if (c->GetState()==unknown) c->ChangeState(Sim.GetTime()+1,high);
  if (c->GetState()==low)     c->ChangeState(Sim.GetTime()+1,high);
  if (c->GetState()==high)    c->ChangeState(Sim.GetTime()+1,low);

  // erlaube neue Auswertung
  actionFlag=false;
}

void Analyzer::ConnectInput (Wire& w, int pin)
{
  // Wird von Connect-Funktion des Drahtes aufgerufen
  if (pin>=0 && pin<n) a[pin] = &w;	
  if (pin==n) b = &w;
}

void Analyzer::ConnectOutput (Wire& w, int pin)
{
  // Wird von Connect-Funktion des Drahtes aufgerufen
  c = &w;
}
