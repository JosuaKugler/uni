// Konstruiere die TM mit Programm und Band
TM::TM (Programm& p, Band& b) : prog(p), band(b)
{
    q=p.Anfangszustand();
}

// einen Schritt machen
void TM::Schritt ()
{
    // lese Bandsymbol
    char s = band.lese();

    // schreibe Band
    if (prog.Richtung(q,s)==Programm::links)
        band.schreibe_links(prog.Ausgabe(q,s));
    else
        band.schreibe_rechts(prog.Ausgabe(q,s));

    // bestimme Folgezustand
    q = prog.Folgezustand(q,s);
}

// Ist Endzustand erreicht?
bool TM::Endzustand ()
{
    if (q==prog.Endzustand()) return true; else return false;
}
  
