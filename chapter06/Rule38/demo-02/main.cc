#include <iostream>

#include "set.h"

using namespace ec;

int main(void) {

  Set<int> set;
  std::cout << set.Size() << std::endl;

  set.Insert(1);
  std::cout << set.Size() << std::endl;

  if(set.Member(1)) {
    std::cout << "1 is in the set" << std::endl;
  }

  set.Remove(1);
  std::cout << set.Size() << std::endl;

  if(set.Member(1)) {
    std::cout << "1 is in the set" << std::endl;
  }
  else {
    std::cout << "1 not is in the set" << std::endl;
  }

  return 0;
}
