Terminal::Terminal (State s)
{
	q = s; // Wert des Terminals
	a=0;   // nix angschlossen
	Sim.StoreCircuitEvent(*this); 
}

Terminal::~Terminal() {}

void Terminal::ChangeInput (State s, int pin) {}

void Terminal::Action ()
{
	// Stosse Draht an
	a->ChangeState(Sim.GetTime()+1,q);
}

void Terminal::ConnectInput (Wire& w, int pin) {}

void Terminal::ConnectOutput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	a = &w;
}
