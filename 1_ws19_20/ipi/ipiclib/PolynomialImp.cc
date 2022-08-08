// Grad auswerten
int Polynomial::degree ()
{
  return maxIndex();
}

// Addition von Polynomen
Polynomial Polynomial::operator+ (Polynomial q)
{
  int nr=degree(); // mein grad

  if (q.degree()>nr) nr=q.degree();

  Polynomial r(nr); // Ergebnispolynom

  for (int i=0; i<=nr; i=i+1)
    {
      if (i<=degree())
        r[i] = r[i]+(*this)[i]; // add me to r
      if (i<=q.degree())
        r[i] = r[i]+q[i];       // add q to r
    }

  return r;
}

// Multiplikation von Polynomen
Polynomial Polynomial::operator* (Polynomial q)
{
  Polynomial r(degree()+q.degree()); // Ergebnispolynom

  for (int i=0; i<=degree(); i=i+1)
    for (int j=0; j<=q.degree(); j=j+1)
      r[i+j] = r[i+j] + (*this)[i]*q[j];

  return r;
}

// Drucken
void Polynomial::print ()
{
  if (degree()<0)
    std::cout << 0;
  else
    std::cout << (*this)[0];
    
  for (int i=1; i<=maxIndex(); i=i+1) 
    std::cout << "+" << (*this)[i] << "*x^" << i;

  std::cout << std::endl;
}
