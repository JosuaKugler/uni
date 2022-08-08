#include <iostream>

int main () 
{
  int n; 
  std::cin >> n;  // d.h. cin.operator>>(n);
  double x;
  std::cin >> x;  // d.h. cin.operator>>(x);
  std::cout << n; // d.h. cout.operator<<(n);
  std::cout << " ";
  std::cout << x;
  std::cout << std::endl; // neue Zeile
  std::cout << n << " " << x << std::endl; 
  return 0;
}
