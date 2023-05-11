#pragma once

#include "Container.h"

#include <string>

class Object {
public:
  virtual std::string toString() const = 0;

protected:
  static int INSTANCE_NUM;
};

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
  int res;
protected:
  std::string status1;
};

class NumObjectsTaskWithResult : public TaskWithResult<int> {
public:
  NumObjectsTaskWithResult() {
    status = "Pending! I will print number of Objects in program";
  }
  void execute() override {
    status = "Done! Number of Objects in program equals " + std::to_string(INSTANCE_NUM);
  }
};


class Named : public Object {
public:
};

