HalfAdder::HalfAdder()
{
  w1.ConnectInput(F1,1);
  w1.ConnectOutput(A,0);
  w2.ConnectInput(F1,0);
  w2.ConnectOutput(N1,0);
  w3.ConnectInput(F2,0);
  w3.ConnectOutput(A,1);
  w4.ConnectInput(F2,1);
  w4.ConnectOutput(N1,1);
  w5.ConnectInput(N1,0);
  w5.ConnectOutput(N2,1);
  w6.ConnectInput(A,0);
  w6.ConnectOutput(F3,0);
  w7.ConnectInput(F3,0);
  w7.ConnectOutput(N2,0);
}

HalfAdder::~HalfAdder() {}

void HalfAdder::ChangeInput (State s, int pin) 
{
  if (pin==0) F1.ChangeInput(s,0);	
  if (pin==1) F2.ChangeInput(s,0);
}

void HalfAdder::Action () {}

void HalfAdder::ConnectInput (Wire& w, int pin)
{
  // Wird von Connect-Funktion des Drahtes aufgerufen
  if (pin==0) F1.ConnectInput(w,0);	
  if (pin==1) F2.ConnectInput(w,0);
}

void HalfAdder::ConnectOutput (Wire& w, int pin)
{
  // Wird von Connect-Funktion des Drahtes aufgerufen
  if (pin==0) N2.ConnectOutput(w,0);	
  if (pin==1) F3.ConnectOutput(w,1);
}
