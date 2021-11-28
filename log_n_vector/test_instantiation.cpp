#include <iostream>
#include <vector>
#include "log_n_vector.h"

class LogInstantiationTestClass {
 public:
  int value_;
  static int instantiated_;
  LogInstantiationTestClass() : value_(0){
    instantiated_++;
  }

  LogInstantiationTestClass(int value) : value_(value) {
    instantiated_++;
  }
};
int LogInstantiationTestClass::instantiated_ = 0;

class StdInstantiationTestClass {
 public:
  int value_;
  static int instantiated_;
  StdInstantiationTestClass() : value_(0){
    instantiated_++;
  }

  StdInstantiationTestClass(int value) : value_(value) {
    instantiated_++;
  }
};
int StdInstantiationTestClass::instantiated_ = 0;

int main()
{
  LogNVector<LogInstantiationTestClass> log_instantiation_test;
  std::vector<StdInstantiationTestClass> std_instantiation_test;
  // std::cout << "log: " << LogInstantiationTestClass::instantiated_ << std::endl
   //          << "std: " << StdInstantiationTestClass::instantiated_ << std::endl;
  for (int i = 0; i < 2048; ++i)
  {
    // std::cout << i << std::endl;
    // std::cout << "\tlog: " << LogInstantiationTestClass::instantiated_ << std::endl
     //          << "\tstd: " << StdInstantiationTestClass::instantiated_ << std::endl;
    log_instantiation_test.push_back(LogInstantiationTestClass(i));
    std_instantiation_test.push_back(StdInstantiationTestClass(i));
  }
  std::cout << "log: " << LogInstantiationTestClass::instantiated_ << std::endl
            << "std: " << StdInstantiationTestClass::instantiated_ << std::endl;
}