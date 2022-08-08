std::ostream& 
operator<< (std::ostream& s, Rational q)
{
  s << q.numerator() << "/" << q.denominator();
  return s;
}
