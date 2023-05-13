#include <iostream>

#include "Container.h"
#include "Object.h"

void testInt() {
  Container<int> cont;

  cont.PushFront(2);
  cont.PushFront(5);
  cont.PushBack(-1);
  cont.PushFront(0);
  cont.PushBack(7);
  cont.PushBack(4);
  std::cout << cont;

  for (auto it = cont.begin(); it != cont.end(); ++it)
    std::cout << *it << " ";
  std::cout << "\n";

  cont.Reverse();
  for (auto it = cont.begin(); it != cont.end(); ++it)
    std::cout << *it << " ";
  std::cout << "\n";

  /*auto itBegin = cont.begin();
  auto itEnd = cont.end();
  std::cout << *itBegin << " " << *itEnd << " " << (itBegin != itEnd) << "\n";*/

  std::cout << int();

  /*auto v1 = cont.Front();
  auto v2 = cont.Back();
  std::cout << cont;

  Container<int> cont1;
  cont1.PushFront(1);
  cont1.PushFront(2);
  cont1.PushBack(3);
  std::cout << cont1;

  cont.Swap(cont1);

  std::cout << cont;
  std::cout << cont1;*/
}

int main() {
  Container<Task*> contTask;
  Container<std::string> contStr;

  Task* task1 = new ArithmeticTask<double>(4, 5, ArithmeticTask<double>::add);
  Task* task2 = new ArithmeticTask<double>(4, 5, ArithmeticTask<double>::subtract);
  Task* task3 = new ArithmeticTask<double>(4, 5, ArithmeticTask<double>::multiply);
  Task* task4 = new ArithmeticTask<double>(4, 5, ArithmeticTask<double>::divide);
  Task* task5 = new NumObjectsTaskWithResult();

  contTask.PushBack(task1);
  contTask.PushBack(task2);
  contTask.PushBack(task3);
  contTask.PushBack(task4);
  contTask.PushBack(task5);

  // Before execution
  for (auto it = contTask.begin(); it != contTask.end(); ++it) {
    contStr.PushBack((*it)->toString());
  }
  for (auto it = contStr.begin(); it != contStr.end(); ++it) {
    std::cout << *it << "\n";
  }

  // After execution
  contStr.Clear();
  for (auto it = contTask.begin(); it != contTask.end(); ++it) {
    (*it)->execute();
    contStr.PushBack((*it)->toString());
  }
  for (auto it = contStr.begin(); it != contStr.end(); ++it) {
    std::cout << *it << "\n";
  }
 

  delete task1;
  delete task2;
  delete task3;
  delete task4;
  delete task5;

  return 0;
}
