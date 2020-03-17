// Methoden fuer die geschachtelte Klasse
Simulator::WireEvent::WireEvent () { w=0; t=0; s=unknown; }

Simulator::WireEvent::WireEvent (Wire& W, int T, State S) {w=&W; t=T; s=S;}

bool Simulator::WireEvent::operator< (WireEvent we)
{
  if (t<we.t) return true;
  if (t==we.t && (reinterpret_cast<unsigned long int>(w)<reinterpret_cast<unsigned long int>(we.w))) return true;
  return false;
}

// Konstruktor
Simulator::Simulator (){time = 0;}

int Simulator::GetTime (){return time;}

void Simulator::StoreWireEvent (Wire& w, int t, State s)
{
  pq.push(WireEvent(w,t,s));
}

void Simulator::StoreCircuitEvent (Circuit& c)
{
  q.push(&c);
}

void Simulator::Simulate (int end)
{
  WireEvent we;

  while (time<=end)
    {
      // Alle Draehte fuer die aktuelle Zeit 
      while (!pq.empty())
	{
	  we = pq.top();        // kleinster Eintrag
	  if (we.t>time) break; // alle Zustaende fuer Zeitschritt OK
	  pq.pop();             // entferne Eintrag
	  (we.w)->Action(we.s); // neuer Zustand
	}

      // Berechne Bausteine zur aktuellen Zeit neu
      while (!q.empty())
	{
	  (q.front())->Action();
	  q.pop();
	}

      // Zeitschritt fertig
      time = time+1;
    }
}

