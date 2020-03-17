#include<iostream>
#include<cassert>

#include "SimpleFloatArray.hh"
#include "SimpleFloatArrayImp.cc"
#include "SimpleFloatArrayIndex.cc"
#include "SimpleFloatArrayCopyCons.cc"
#include "SimpleFloatArrayAssign.cc"

#include "CheckedSimpleFloatArray.hh"
#include "CheckedSimpleFloatArrayImp.cc"

void g (SimpleFloatArray& a) {
  std::cout << "beginn in g: " << std::endl;
  std::cout << "access: " << a[1] << "  " << a[10] << std::endl;
  std::cout << "ende in g: " << std::endl;
}

int main () {
  CheckedSimpleFloatArray a(10,0);
  g(a);
  std::cout << "beginn in main: " << std::endl;
  std::cout << "zugriff in main: " << a[10] << std::endl;
  std::cout << "ende in main: " << std::endl;
}
