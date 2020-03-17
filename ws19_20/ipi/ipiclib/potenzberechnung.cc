#include "fcpp.hh"

int quadrat(int x)
{
  return x*x;
}

int potenz(int x, int exp)
{
    return cond(
      x>1,
      cond(
        exp%2==0,
        quadrat(potenz(x, exp/2)),
        x*potenz(x, exp-1)
      ),
      x
    );
}

int main() {
  return print(potenz(2,3));
}
