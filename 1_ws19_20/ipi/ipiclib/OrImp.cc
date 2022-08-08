Or::Or()
{
	a=b=c=0; // nix angschlossen
	actionFlag=false;
}

Or::~Or() {}

void Or::ChangeInput (State s, int pin)
{
	// Sorge dafuer, dass Gatter neu berechnet wird, wenn
    // alle Zustaende der Eingaenge (Draehte) festliegen
	if (!actionFlag)
	{
		Sim.StoreCircuitEvent(*this);
		actionFlag=true;
	}
}

void Or::Action ()
{
	// Lese Eingangssignale
	State A = a->GetState();
	State B = b->GetState();
	State Output=unknown;

	// Wertetabelle
	if (A==low && B==low)  Output=low;
	if (A==high|| B==high) Output=high; 

	// Setze Draht 	
	if (c!=0) c->ChangeState(Sim.GetTime()+3,Output);

	// erlaube neue Auswertung
	actionFlag=false;
}

void Or::ConnectInput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	if (pin==0) a = &w;	
	if (pin==1) b = &w;
}

void Or::ConnectOutput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	c = &w;
}
