#include <iostream>

#include "Container.h"
#include "Object.h"

//template <typename T>
//class A {
//public :
//  T res;
//};


int main() {
  Container<Task*> contTask;
  Container<std::string> contStr;

  std::cout << "-----TASKS-INIT-----\n";
  Task* tasks[10];
  tasks[0] = new CountResTaskWithResult(contTask);
  tasks[1] = new ArithmeticTask<double>(4, 5, Operation::subtract);
  tasks[2] = new ArithmeticTask<double>(4, 5, Operation::multiply);
  tasks[3] = new ArithmeticTask<double>(4, 5, Operation::add);
  tasks[4] = new ArithmeticTask<double>(4, 5, Operation::divide);
  tasks[5] = new NumObjectsTaskWithResult();
  tasks[6] = new AppendTask(contTask, tasks[5]);
  tasks[7] = new NumObjectsTaskWithResult();
  tasks[8] = new CleanupTask(contTask);
  tasks[9] = new AppendTask(contTask, tasks[8]);

  contTask.PushFront(tasks[0]); //fr
  contTask.PushBack(tasks[1]);
  contTask.PushFront(tasks[2]); //fr
  contTask.PushBack(tasks[3]);
  contTask.PushFront(tasks[4]); //fr
  contTask.PushBack(tasks[6]);
  contTask.PushFront(tasks[7]); //fr
  contTask.PushBack(tasks[9]);
 

  std::cout << "-----TASKS-INFO-----\n";
  std::cout << "Number of objects on start " << Object::getInstanceNum() << "\n";
  for (auto it = contTask.begin(); it != contTask.end(); ++it) {
    contStr.PushBack((*it)->toString());
  }
  for (auto it = contStr.begin(); it != contStr.end(); ++it) {
    std::cout << *it << "\n";
  }

  std::cout << "-----TASKS-EXECUTION-----\n";
  contStr.Clear();
  while (!contTask.Empty()) {
    Task* t = contTask.Front();
    contTask.PopFront();
    t->execute();
    contStr.PushBack(t->toString());
  }
  for (auto it = contStr.begin(); it != contStr.end(); ++it) {
    std::cout << *it << "\n";
  }
 

  std::cout << "-----MEMORY-CLEANUP-----\n";
  for (int i = 0; i < 10; ++i)
    delete tasks[i];
  std::cout << "Number of objects on end " << Object::getInstanceNum() << "\n";
  return 0;
}
