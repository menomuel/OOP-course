#pragma once

#include "Container.h"

#include <string>
#include <typeinfo> 

class Object {
public:
  virtual std::string toString() const = 0;

protected:
  static int INSTANCE_NUM;
};

int Object::INSTANCE_NUM = 0;

class Named : public Object {};

class Task : public Object {
public:
  virtual void execute() = 0;
  std::string toString() const override {
    return status;
  }
protected:
  std::string status;
};

template <typename T>
class TaskWithResult : public Task {
protected:
  T res;
};

// Final classes

template <typename T>//, typename std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr>
class ArithmeticTask final : public TaskWithResult<T> {
public:
  enum Operation {
    add,
    subtract,
    multiply,
    divide
  };

  ArithmeticTask(const T& v1, const T& v2, Operation op) : m_v1(v1), m_v2(v2), m_op(op) {
    std::string opLiteral;
    switch (m_op)
    {
    case add: opLiteral = "+"; break;
    case subtract: opLiteral = "-"; break;
    case multiply: opLiteral = "*"; break;
    case divide: opLiteral = "/"; break;
    default:
      break;
    }
    m_strOperation = std::to_string(m_v1) + opLiteral + std::to_string(m_v2);
    this->status = "Pending! I will perform arithmetic operation " + m_strOperation;
    ++Object::INSTANCE_NUM;
  }

  void execute() override {
    auto f = [](const T& v1, const T& v2, Operation op) {
      switch (op)
      {
      case add: return v1 + v2;
      case subtract: return v1 - v2;
      case multiply: return v1 * v2;
      case divide: return v1 / v2;
      default: return T();
      }
    };
    this->res = f(m_v1, m_v2, m_op);
    this->status = "Done! Arithmetic operation " + m_strOperation + " = " + std::to_string(this->res);
  }

private:
  T m_v1, m_v2;
  Operation m_op;
  std::string m_strOperation;
};

class AppendTask final : public Task {
public:
  AppendTask(Container<Task*> cont, Task* task) : m_cont(cont), m_task(task) {
    status = "Pending! I will add task to container of tasks";
  }
  void execute() override {
    m_cont.PushBack(m_task);
    status = "Done! Task appended to Container";
  }
private:
  Container<Task*> m_cont;
  Task* m_task;
};

class CountNamedTaskWithResult final : public TaskWithResult<int> {
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
};

class CountResTaskWithResult final : public TaskWithResult<int> {
public:
  CountResTaskWithResult(const Container<Task*>& cont) : m_cont(cont) {
    status = "Pending! I will print number of tasks with result";
  }
  void execute() override {
    res = 0;
    for (auto it = m_cont.cbegin(); it != m_cont.cend(); ++it) {
      if (TaskWithResult* twr = dynamic_cast<TaskWithResult*>(*it))
        ++res;
    }
    status = "Done! Number of tasks with result equals " + std::to_string(res);
  }
private:
  const Container<Task*>& m_cont;
};

class CleanupTask final : public Task {
public:
  CleanupTask(Container<Object*>& cont) : m_cont(cont) {
    status = "Pending! I will empty the container";
  }
  void execute() override {
    m_cont.Clear();
    status = "Done! Container now empty\n";
  }

private:
  Container<Object*>& m_cont;
};

class NumObjectsTaskWithResult final : public TaskWithResult<int> {
public:
  NumObjectsTaskWithResult() {
    status = "Pending! I will print number of Objects in program";
  }
  void execute() override {
    res = Object::INSTANCE_NUM;
    status = "Done! Number of Objects in program equals " + std::to_string(res);
  }
};
