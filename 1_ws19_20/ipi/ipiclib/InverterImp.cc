Inverter::Inverter()
{
	a=b=0; // nix angschlossen
	actionFlag=false;
}

Inverter::~Inverter() {}

void Inverter::ChangeInput (State s, int pin)
{
	// Sorge dafuer, dass Gatter neu berechnet wird, wenn
    // alle Zustaende der Eingaenge (Draehte) festliegen
	if (!actionFlag)
	{
		Sim.StoreCircuitEvent(*this);
		actionFlag=true;
	}
}

void Inverter::Action ()
{
	// Lese Eingangssignale
	State A = a->GetState();
	State Output=unknown;

	// Wertetabelle
	if (A==low )  Output=high;
	if (A==high)  Output=low;

	if (b!=0) b->ChangeState(Sim.GetTime()+3,Output);

	// erlaube neue Auswertung
	actionFlag=false;
}

void Inverter::ConnectInput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	a = &w;	
}

void Inverter::ConnectOutput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	b = &w;
}
