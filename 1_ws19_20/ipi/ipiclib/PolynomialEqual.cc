bool Polynomial::operator== (Polynomial q)
{
  if (q.degree()>degree())
    {
      for (int i=0; i<=degree(); i=i+1)
        if ((*this)[i]!=q[i]) return false;
      for (int i=degree()+1; i<=q.degree(); i=i+1)
        if (q[i]!=0.0) return false;
    }
  else
    {
      for (int i=0; i<=q.degree(); i=i+1)
        if ((*this)[i]!=q[i]) return false;
      for (int i=q.degree()+1; i<=degree(); i=i+1)
        if ((*this)[i]!=0.0) return false;
    }

  return true;
}
