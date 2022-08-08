Clock::Clock (int m, State initial)
{
	init = initial;                    // Merken
	n = m;                             // Merke Taktrate
	a = b = c = 0;                     // nix angeschlossen
	actionFlag=false;                  // nix aktiviert
	w.ConnectInput(*this,1);           // Ich -> Draht
	w.ConnectOutput(*this,0);          // Draht->Ich
	Sim.StoreCircuitEvent(*this);
}

Clock::~Clock() {}

void Clock::ChangeInput (State s, int pin)
{
	// Sorge dafuer, dass Gatter neu berechnet wird, wenn
    // alle Zustaende der Eingaenge (Draehte) festliegen
	if (!actionFlag)
	{
		Sim.StoreCircuitEvent(*this);
		actionFlag=true;
	}
}

void Clock::Action ()
{
	// Selbstaktivierung nach n Takten
	if (c->GetState()==unknown)  
	{
		c->ChangeState(Sim.GetTime()+1,init);
		b->ChangeState(Sim.GetTime()+1,init);
	}
	if (c->GetState()==low)  
	{
		c->ChangeState(Sim.GetTime()+n,high);
		b->ChangeState(Sim.GetTime()+n,high);
	}
	if (c->GetState()==high) 
	{
		c->ChangeState(Sim.GetTime()+n,low);
		b->ChangeState(Sim.GetTime()+n,low);
	}

	// erlaube neue Auswertung
	actionFlag=false;
}

void Clock::ConnectInput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	a = &w;	
}

void Clock::ConnectOutput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	if (pin==0) b = &w;
	if (pin==1) c = &w;
}
