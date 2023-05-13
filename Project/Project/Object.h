#pragma once

#include "Container.h"

#include <string>
#include <typeinfo> 

class Object {
public:
  virtual std::string toString() const = 0;
  static int getInstanceNum() { return INSTANCE_NUM; }

protected:
  static int INSTANCE_NUM;
};

int Object::INSTANCE_NUM = 0;

class Named : public Object {};

namespace Operation {
  enum Arithmetic {
    add,
    subtract,
    multiply,
    divide
  };
};

class Task : public Object {
public:
  Task() { ++INSTANCE_NUM; }
  virtual ~Task() { --INSTANCE_NUM; }

  virtual void execute() {};
  std::string toString() const override {
    return status;
  }

protected:
  std::string status;
};

//template <typename T>
class TaskWithResult : public Task {
//protected:
//  T res;
};

// Final classes

template <typename T, typename std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr>
class ArithmeticTask final : public TaskWithResult {
public:
  ArithmeticTask(const T& v1, const T& v2, Operation::Arithmetic op) : m_v1(v1), m_v2(v2), m_op(op) {
    std::string opLiteral;
    switch (m_op)
    {
    case Operation::add: opLiteral = "+"; break;
    case Operation::subtract: opLiteral = "-"; break;
    case Operation::multiply: opLiteral = "*"; break;
    case Operation::divide: opLiteral = "/"; break;
    default: break;
    }
    m_strOperation = std::to_string(m_v1) + opLiteral + std::to_string(m_v2);
    this->status = "Pending! I will perform arithmetic operation " + m_strOperation;
  }

  void execute() override {
    auto f = [](const T& v1, const T& v2, Operation::Arithmetic op) {
      switch (op)
      {
      case Operation::add: return v1 + v2;
      case Operation::subtract: return v1 - v2;
      case Operation::multiply: return v1 * v2;
      case Operation::divide: return v1 / v2;
      default: return T();
      }
    };
    res = f(m_v1, m_v2, m_op);
    this->status = "Done! Arithmetic operation " + m_strOperation + " = " + std::to_string(res);
  }

private:
  T m_v1, m_v2;
  T res;
  Operation::Arithmetic m_op;
  std::string m_strOperation;
};

class AppendTask final : public Task {
public:
  AppendTask(Container<Task*>& cont, Task* task) : m_cont(cont), m_task(task) {
    status = "Pending! I will add task to container of tasks which says \"" + task->toString() + "\"";
  }
  void execute() override {
    m_cont.PushBack(m_task);
    status = "Done! Task appended to Container";
  }

private:
  Container<Task*>& m_cont;
  Task* m_task;
};

class CountNamedTaskWithResult final : public TaskWithResult {
public:
  CountNamedTaskWithResult(const Container<Object*>& cont) : m_cont(cont) {
    status = "Pending! I will print number of named objects";
  }
  void execute() override {
    res = 0;
    for (auto it = m_cont.cbegin(); it != m_cont.cend(); ++it) {
      if (Named* named = dynamic_cast<Named*>(*it))
        ++res;
    }
    status = "Done! Number of named objects equals " + std::to_string(res);
  }

private:
  const Container<Object*>& m_cont;
  int res;
};

class CountResTaskWithResult final : public TaskWithResult {
public:
  CountResTaskWithResult(const Container<Task*>& cont) : m_cont(cont) {
    status = "Pending! I will print number of tasks with result";
  }
  void execute() override {
    res = 0;
    for (auto it = m_cont.cbegin(); it != m_cont.cend(); ++it) {
      TaskWithResult* twr = dynamic_cast<TaskWithResult*>(*it);
      if (twr)
        ++res;
    }
    status = "Done! Number of tasks with result equals " + std::to_string(res);
  }

private:
  const Container<Task*>& m_cont;
  int res;
};

class CleanupTask final : public Task {
public:
  CleanupTask(Container<Task*>& cont) : m_cont(cont) {
    status = "Pending! I will empty the container";
  }
  void execute() override {
    m_cont.Clear();
    status = "Done! Container now empty\n";
  }

private:
  Container<Task*>& m_cont;
};

class NumObjectsTaskWithResult final : public TaskWithResult {
public:
  NumObjectsTaskWithResult() {
    status = "Pending! I will print number of Objects in program";
  }
  void execute() override {
    status = "Done! Number of Objects in program equals " + std::to_string(INSTANCE_NUM);
  }
};
