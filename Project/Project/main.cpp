#include <iostream>

#include "Container.h"
#include "Object.h"

int main() {

  Container<int> cont;

  cont.PushFront(2);
  cont.PushFront(5);
  cont.PushBack(-1);
  cont.PushFront(0);
  cont.PushBack(7);
  cont.PushBack(4);
  std::cout << cont;

  auto v1 = cont.Front();
  auto v2 = cont.Back();
  std::cout << cont;

  Container<int> cont1;
  cont1.PushFront(1);
  cont1.PushFront(2);
  cont1.PushBack(3);
  std::cout << cont1;

  cont.Swap(cont1);

  std::cout << cont;
  std::cout << cont1;

  return 0;
}
