#include "fcpp.hh"

int ggT (int a, int b)
{
  return cond( b==0 , a , ggT(b,a%b) );
}


int main (int argc, char** argv)
{
  return print(ggT(readarg_int(argc,argv,1),
		   readarg_int(argc,argv,2)));
}
