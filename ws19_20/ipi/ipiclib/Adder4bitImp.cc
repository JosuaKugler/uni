Adder4Bit::Adder4Bit()
{
	w0.ConnectInput(fa0,1);
	w0.ConnectOutput(fa1,0);
	w1.ConnectInput(fa1,1);
	w1.ConnectOutput(fa2,0);
	w2.ConnectInput(fa2,1);
	w2.ConnectOutput(fa3,0);
}

Adder4Bit::~Adder4Bit() {}

void Adder4Bit::ChangeInput (State s, int pin) 
{
	if (pin==0) fa0.ChangeInput(s,1);	
	if (pin==1) fa1.ChangeInput(s,1);	
	if (pin==2) fa2.ChangeInput(s,1);	
	if (pin==3) fa3.ChangeInput(s,1);	
	if (pin==4) fa0.ChangeInput(s,2);	
	if (pin==5) fa1.ChangeInput(s,2);	
	if (pin==6) fa2.ChangeInput(s,2);	
	if (pin==7) fa3.ChangeInput(s,2);	
	if (pin==8) fa0.ChangeInput(s,0);	
}

void Adder4Bit::Action () {}

void Adder4Bit::ConnectInput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	if (pin==0) fa0.ConnectInput(w,1);	
	if (pin==1) fa1.ConnectInput(w,1);	
	if (pin==2) fa2.ConnectInput(w,1);	
	if (pin==3) fa3.ConnectInput(w,1);	
	if (pin==4) fa0.ConnectInput(w,2);	
	if (pin==5) fa1.ConnectInput(w,2);	
	if (pin==6) fa2.ConnectInput(w,2);	
	if (pin==7) fa3.ConnectInput(w,2);	
	if (pin==8) fa0.ConnectInput(w,0);	
}

void Adder4Bit::ConnectOutput (Wire& w, int pin)
{
	// Wird von Connect-Funktion des Drahtes aufgerufen
	if (pin==0) fa0.ConnectOutput(w,0);	
	if (pin==1) fa1.ConnectOutput(w,0);	
	if (pin==2) fa2.ConnectOutput(w,0);	
	if (pin==3) fa3.ConnectOutput(w,0);	
	if (pin==4) fa3.ConnectOutput(w,1);	
}
