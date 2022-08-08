Wire::Wire ()
{
  // Initialisiere mit unbekanntem Zustand
  q = unknown;
}

inline State Wire::GetState ()
{
  return q;
}


void Wire::ChangeState (int t, State s)
{
  Sim.StoreWireEvent(*this,t,s);
}

void Wire::Action (State s)
{
  if (s==q) return;      // nix zu tun
  q = s;                 // neuer Zustand
  c->ChangeInput(q,pin); // Nachricht an angeschlossen Baustein 
}

void Wire::ConnectInput (Circuit& cir, int i)
{
  // Merke NICHT an wen ich angeschlossen bin
  // aber Baustein muss mich kennen.
  cir.ConnectOutput(*this,i);
}

void Wire::ConnectOutput (Circuit& cir, int i)
{
  // Merke Baustein, an den der Ausgang angeschlossen ist
  c = &cir;
  pin = i;
  // Rueckverbindung Baustein an Draht
  c->ConnectInput(*this,pin);
}
