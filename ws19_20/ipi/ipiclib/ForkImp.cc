Fork::Fork()
{
  a=b=c=0; // nix angschlossen
}

Fork::~Fork() {}

void Fork::ChangeInput (State s, int pin)
{
  // Leite Eingang SOFORT an beide Ausgaenge weiter
  if (b!=0) b->ChangeState(Sim.GetTime(),s);
  if (c!=0) c->ChangeState(Sim.GetTime(),s);
}

void Fork::Action ()
{
  // nix zu tun
}

void Fork::ConnectInput (Wire& w, int pin)
{
  // Wird von Connect-Funktion des Drahtes aufgerufen
  a = &w;	
}

void Fork::ConnectOutput (Wire& w, int pin)
{
  // Wird von Connect-Funktion des Drahtes aufgerufen
  if (pin==0) b = &w;
  if (pin==1) c = &w;
}
