namespace A {
  int n = 1;
  int m = n;
}

namespace B {
  int n = 2;
  class X {};
}

namespace C {
  double x;
  int f (double x) {return x;}
  namespace D {
    double x,y;
    int f (double x) {return x;}
  }
}

namespace C {
  double y;
}

int main () 
{
  A::n = B::n + 3;

  C::x = 0.0;
  C::y = 1.0;
  C::D::y = 2.0;
  C::f(2.0);

  return 0;
}
