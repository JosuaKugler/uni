#include<cassert>
#include<iostream>

#include"DLL.hh"
#include"Stack.hh"

int main ()
{
  Stack<int> s1;
  for (int i=1; i<=5; i++)
    s1.push(i);
    
  Stack<int> s2(s1);
  s2 = s1;
  while (!s2.empty())
    {
      std::cout << s2.top() << std::endl;
      s2.pop();
    }
}
