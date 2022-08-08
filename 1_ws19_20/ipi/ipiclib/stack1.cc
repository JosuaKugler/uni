#include "fcpp.hh"

typedef int element_type;   // Integer-Stack

// START stack-library ...

const int stack_size = 1000;

element_type stack[stack_size];
int top = 0;  // Stapelzeiger

// Stack-Operationen

void push (element_type e)
{
  stack[top] = e;
  top = top+1;
}

bool empty ()
{
  return top==0;
}

element_type pop ()
{
  top = top-1;
  return stack[top];
}

int main ()
{
  push(4);
  push(5);
  while (!empty())
    print(pop());
  return 0;
}

