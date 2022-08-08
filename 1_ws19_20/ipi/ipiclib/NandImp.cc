Nand::Nand()
{
  a=b=c=0; // nix angschlossen
  actionFlag=false;
}

Nand::~Nand() {}

void Nand::ChangeInput (State s, int pin)
{
  // Sorge dafuer, dass Gatter neu berechnet wird
  if (!actionFlag)
    {
      Sim.StoreCircuitEvent(*this);
      actionFlag=true;
    }
}

void Nand::Action ()
{
  // Lese Eingangssignale
  State A = a->GetState();
  State B = b->GetState();
  State Output=unknown;

  // Wertetabelle
  if (A==high&& B==high) Output=low;
  if (A==low || B==low ) Output=high;

  // Setze Draht 	
  if (c!=0) c->ChangeState(Sim.GetTime()+3,Output);

  // erlaube neue Auswertung
  actionFlag=false;
}

void Nand::ConnectInput (Wire& w, int pin)
{
  // Wird von Connect-Funktion des Drahtes aufgerufen
  if (pin==0) a = &w;	
  if (pin==1) b = &w;
}

void Nand::ConnectOutput (Wire& w, int pin)
{
  // Wird von Connect-Funktion des Drahtes aufgerufen
  c = &w;
}
