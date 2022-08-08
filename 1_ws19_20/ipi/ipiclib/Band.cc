Band::Band (std::string s, char init)
{
  // initialisiere Band mit dem Symbol init
  for (int i=0; i<Band::N; i++) band[i] = init;

  // Lese Zeichenkette
  if (s.size()>Band::N)
    {
      print("Band zu klein");
      return;
    }
  for (int i=0; i<s.size(); i++) band[i] = s[i];
  print(s.size()," Symbole auf Band initialisiert ",0);

  // Setze aktuelle Bandposition auf Anfang
  pos = 0;

  // Initialisiere maximal benutzten Bandabschnitt
  benutzt = s.size();
}

char Band::lese ()
{
  return band[pos];
}

void Band::schreibe_links (char symbol)
{
  if (pos<0)
    {
      print("Versuch ueber linkes Bandende zu laufen!");
      return;
    }

  band[pos] = symbol;
  if (pos>=benutzt) benutzt = pos+1;
  pos = pos-1;
}

void Band::schreibe_rechts (char symbol)
{
  if (pos>=Band::N-1)
    {
      print("Versuch ueber rechtes Bandende zu laufen!");
      return;
    }

  band[pos] = symbol;
  if (pos>=benutzt) benutzt = pos+1;
  pos = pos+1;
}

void Band::drucke ()
{
  char kopie[N+3];
  int j=0;
  for (int i=0; i<pos; i++) {
    kopie[j] = band[i];
    j = j+1;
  }
  kopie[j] = '[';
  kopie[j+1] = band[pos];
  kopie[j+2] = ']';
  j = j+3;
  for (int i=pos+1; i<benutzt; i++) {
    kopie[j] = band[i];
    j = j+1;
  }
  kopie[j] = 0; // Ende Zeichen
  print(kopie);
}
