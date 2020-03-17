int Rational::numerator () {
  return n;
}

int Rational::denominator () {
  return d;
}

void Rational::print () {
  ::print(n,"/",d,0);
}

// ggT zum kuerzen
int Rational::ggT (int a, int b) {
  return (b==0) ? a : ggT(b,a%b);
}

// Konstruktoren
Rational::Rational (int num, int denom)
{
  int t = ggT(num,denom);
  if (t!=0)
    {
      n=num/t;
      d=denom/t;
    }
  else
    {
      n = num;
      d = denom;
    }
}

Rational::Rational (int num) {
  n=num;
  d=1;
}

Rational::Rational () {
  n=0;
  d=1;
}

// Operatoren
Rational Rational::operator+ (Rational q) {
  return Rational(n*q.d+q.n*d,d*q.d);
}

Rational Rational::operator- (Rational q) {
  return Rational(n*q.d-q.n*d, d*q.d);
}

Rational Rational::operator* (Rational q) {
  return Rational(n*q.n, d*q.d);
}

Rational Rational::operator/ (Rational q) {
  return Rational(n*q.d,d*q.n);
}
