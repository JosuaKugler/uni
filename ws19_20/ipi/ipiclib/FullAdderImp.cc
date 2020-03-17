FullAdder::FullAdder()
{
	w1.ConnectInput(ha1,0);
	w1.ConnectOutput(ha2,0);
	w2.ConnectInput(ha1,1);
	w2.ConnectOutput(A,0);
	w3.ConnectInput(ha2,1);
	w3.ConnectOutput(A,1);
}

FullAdder::~FullAdder() {}

void FullAdder::ChangeInput (State s, int pin) 
{
	if (pin==0) ha2.ChangeInput(s,1);	
	if (pin==1) ha1.ChangeInput(s,1);
	if (pin==2) ha1.ChangeInput(s,0);
}

void FullAdder::Action () {}

void FullAdder::ConnectInput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	if (pin==0) ha2.ConnectInput(w,1);	
	if (pin==1) ha1.ConnectInput(w,1);
	if (pin==2) ha1.ConnectInput(w,0);
}

void FullAdder::ConnectOutput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	if (pin==0) ha2.ConnectOutput(w,0);	
	if (pin==1) A.ConnectOutput(w,0);
}
