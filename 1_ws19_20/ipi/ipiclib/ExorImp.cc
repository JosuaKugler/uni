Exor::Exor()
{
	a=b=c=0; // nix angschlossen
	actionFlag=false;
}

Exor::~Exor() {}

void Exor::ChangeInput (State s, int pin)
{
	// Sorge dafuer, dass Gatter neu berechnet wird, wenn
    // alle Zustaende der Eingaenge (Draehte) festliegen
	if (!actionFlag)
	{
		Sim.StoreCircuitEvent(*this);
		actionFlag=true;
	}
}

void Exor::Action ()
{
	// Lese Eingangssignale
	State A = a->GetState();
	State B = b->GetState();

	// Wertetabelle
	if (A==low && B==low)  c->ChangeState(Sim.GetTime()+3,low);
	if (A==low && B==high) c->ChangeState(Sim.GetTime()+3,high);
	if (A==high&& B==low)  c->ChangeState(Sim.GetTime()+3,high);
	if (A==high&& B==high) c->ChangeState(Sim.GetTime()+3,low);

	// unbekannt
	if (A==unknown||B==unknown)
		if (c!=0) c->ChangeState(Sim.GetTime()+3,unknown);

	// erlaube neue Auswertung
	actionFlag=false;
}

void Exor::ConnectInput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	if (pin==0) a = &w;	
	if (pin==1) b = &w;
}

void Exor::ConnectOutput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	c = &w;
}
