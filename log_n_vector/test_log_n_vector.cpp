/*
  File name: test_log_n_vector.cpp
  @author Sarah Youngquist
  Program Purpose: Benchmarking for log_n_vector.h
 * For Foothill College Class: F21 CS F002C Data Structures and Algorithms in C++
 * Homework 2 O(log(N)) Vector Due 2021-10-04
 */

#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <list>

#include "log_n_vector.h"
#include "no_bits_vector.h"

const int MAXIMUM = 1000000;
const int REPS = 500;
const int PAST = 50;

std::pair<double, double> test_insert(int maximum, int reps);
std::pair<double, double> test_bits_insert(int maximum, int reps);
std::vector<std::pair<double, double>> time_insert_by_index(int maximum, int reps);
std::vector<std::pair<double, double>> test_insert_amortized(int maximum, int reps, int past_num);
std::vector<std::pair<double, double>> time_access(int maximum, int reps);

class SimpleTimer {
  std::chrono::time_point<std::chrono::steady_clock> start_time;
 public:
  void start() {
    start_time = std::chrono::steady_clock::now();
  }
  double elapsed_seconds() const {
    std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start_time;
    return elapsed.count();
  }
};

int main() {
  std::pair<double, double> result = test_bits_insert(MAXIMUM, REPS);
  std::cout.precision(std::numeric_limits<double>::max_digits10 - 1);
  std::cout << result.first << " " << result.second << "\n\n";

  /*
  for (int i = 0; i < MAXIMUM; ++i)
  {
    int index = i;
    // = amortized_insert_results[index - 1];
    // std::cout << (index - 1) << "," << p.first << "," << p.second << std::endl;
    std::pair<double, double> p = amortized_insert_results[index];
    std::cout << index << "," << p.first << "," << p.second << std::endl;
  }
   */
}

std::pair<double, double> test_insert(int maximum, int reps)
{
  SimpleTimer timer;
  double log_n_time, std_time;
  // LogNVector
  timer.start();
  for (int i = 0; i < reps; ++i)
  {
    LogNVector<int> v;
    for (int j = 0; j < maximum; ++j) {
      v.push_back(j);
    }
  }
  auto stop = std::chrono::steady_clock::now();
  log_n_time = timer.elapsed_seconds();
  // std::vector
  timer.start();
  for (int i = 0; i < reps; ++i)
  {
    std::vector<int> v;
    for (int j = 0; j < maximum; ++j) {
      v.push_back(j);
    }
  }
  std_time = timer.elapsed_seconds();

  return {log_n_time, std_time};
}

std::pair<double, double> test_bits_insert(int maximum, int reps)
{
  SimpleTimer timer;
  double log_n_time, no_bit_time;
  // LogNVector
  timer.start();
  for (int i = 0; i < reps; ++i)
  {
    LogNVector<int> v;
    for (int j = 0; j < maximum; ++j) {
      v.push_back(j);
    }
  }
  auto stop = std::chrono::steady_clock::now();
  log_n_time = timer.elapsed_seconds();
  // no bits
  timer.start();
  for (int i = 0; i < reps; ++i)
  {
    NoBitsVector<int> v;
    for (int j = 0; j < maximum; ++j) {
      v.push_back(j);
    }
  }
  no_bit_time = timer.elapsed_seconds();

  return {log_n_time, no_bit_time};
}

std::vector<std::pair<double, double>> time_insert_by_index(int maximum, int reps)
{
  std::vector<std::pair<double, double>> times;

  std::vector<LogNVector<int>> log_n_vectors;
  std::vector<std::vector<int>> std_vectors;
  // one vector for reach rep
  for (int i = 0; i < reps; ++i)
  {
    log_n_vectors.push_back(LogNVector<int>());
    std_vectors.push_back(std::vector<int>());
  }
  // find time for each index
  for (int index = 0; index < maximum; ++index)
  {
    double log_n_time, std_time;
    // LogNVector
    SimpleTimer timer;
    timer.start();
    for (int i = 0; i < reps; ++i)
    {
      log_n_vectors[i].push_back(index);
    }
    log_n_time = timer.elapsed_seconds();
    // std::vector
    timer.start();
    for (int i = 0; i < reps; ++i)
    {
      std_vectors[i].push_back(index);
    }
    std_time = timer.elapsed_seconds();
    times.push_back({log_n_time, std_time});
  }
  return times;
}


std::vector<std::pair<double, double>> test_insert_amortized(int maximum, int reps, int past_num)
{
  std::vector<std::pair<double, double>> times;

  std::vector<LogNVector<int>> log_n_vectors;
  std::vector<std::vector<int>> std_vectors;
  // one vector for reach rep
  for (int i = 0; i < reps; ++i)
  {
    log_n_vectors.push_back(LogNVector<int>());
    std_vectors.push_back(std::vector<int>());
  }

  double log_n_time = 0, std_time = 0;
  std::list<double> log_times;
  std::list<double> std_times;
  // find time for each index

  for (int index = 0; index < maximum; ++index)
  {
    double elapsed, elapsed1;
    // LogNVector
    SimpleTimer timer;
    timer.start();
    for (int i = 0; i < reps; ++i)
    {
      log_n_vectors[i].push_back(index);
    }
    elapsed = timer.elapsed_seconds();
    log_n_time += elapsed;
    log_times.push_back(elapsed);
    if (index >= past_num)
    {
      log_n_time -= log_times.front();
      log_times.pop_front();
    }
    // std::vector
    timer.start();
    for (int i = 0; i < reps; ++i)
    {
      std_vectors[i].push_back(index);
    }
    elapsed1 = timer.elapsed_seconds();
    std_time += elapsed1;
    std_times.push_back(elapsed1);
    if (index >= past_num)
    {
      std_time -= std_times.front();
      std_times.pop_front();
    }

    times.push_back({log_n_time, std_time});
  }
  return times;
}

std::vector<std::pair<double, double>> time_access(int maximum, int reps)
{
  std::vector<std::pair<double, double>> times;

  LogNVector<int> log_n_vector;
  std::vector<int> std_vector;
  for (int i = 0; i < maximum; ++i)
  {
    log_n_vector.push_back(i);
    std_vector.push_back(i);
  }
  // find time for each index
  for (int index = 0; index < maximum; ++index)
  {
    int temp;
    double log_n_time, std_time;
    // LogNVector
    SimpleTimer timer;
    timer.start();
    for (int i = 0; i < reps; ++i)
    {
      temp = log_n_vector[index];
    }
    log_n_time = timer.elapsed_seconds();
    // std::vector
    timer.start();
    for (int i = 0; i < reps; ++i)
    {
      temp = std_vector[index];
    }
    std_time = timer.elapsed_seconds();
    times.push_back({log_n_time, std_time});
  }
  return times;
}
/*
RESULTS:
 Insertion: Maximum 100000, reps 50      LogNVector: 0.219614    std::vector: 0.34042
Insertion: Maximum 1000000, reps 50     LogNVector: 2.40845     std::vector: 3.68354
Insertion: Maximum 10000000, reps 5     LogNVector: 2.37015     std::vector: 4.09991
Insertion: Maximum 100000000, reps 5    LogNVector: 25.247      std::vector: 63.4175

  // std::pair<double, double> insertion_results = test_insert(MAXIMUM, REPS);
  // std::cout << "Insertion: Maximum " << MAXIMUM << ", reps " << REPS << "\tLogNVector: " << insertion_results.first <<  "\tstd::vector: " << insertion_results.second << std::endl;


   std::cout.precision(std::numeric_limits<double>::max_digits10 - 1);
  std::vector<std::pair<double, double>> insert_by_index_results = time_insert_by_index(MAXIMUM, REPS);
  int max_show = std::numeric_limits<unsigned int>::digits - std::countl_zero((unsigned int) MAXIMUM);
  std::cout << "index,log_vector/std_vector,std_vector/log_vector,log_vector,std_vector\n";
  for (int i = 0; i < max_show; ++i)
  {
    int index = 1 << i;
    std::pair<double, double> p = insert_by_index_results[index - 1];
    std::cout << (index - 1) << "," << (p.first / p.second) << "," << (p.second / p.first) << "," << p.first << "," << p.second << std::endl;
    p = insert_by_index_results[index];
    std::cout << index << "," << (p.first / p.second) << "," << (p.second / p.first) << "," << p.first << "," << p.second << std::endl;
  }


Basic test displays
   for (int i = 0; i < 50; ++i)
  {
    log_vector.push_back(i);
    std::cout << "size: " << log_vector.size() << ", capacity: " << log_vector.capacity() << std::endl;
    std::cout << "vector: \n";
    log_vector.Display();
    int popped = log_vector.pop_back();
    std::cout << "popped: " << popped << ", size: " << log_vector.size() << ", capacity: " << log_vector.capacity() << std::endl;
    std::cout << "vector: \n";
    log_vector.Display();
    log_vector.push_back(i);
    std::cout << "size: " << log_vector.size() << ", capacity: " << log_vector.capacity() << std::endl;
    std::cout << "vector: \n";
    log_vector.Display();
    std::cout << std::endl << std::endl;
  }

  // pretty by index insertion output (pows of 2)
  int max_show = std::numeric_limits<unsigned int>::digits - std::countl_zero((unsigned int) MAXIMUM);
    std::vector<std::pair<double, double>> insert_by_index_results = time_insert_by_index(MAXIMUM, REPS);
  int max_show = std::numeric_limits<unsigned int>::digits - std::countl_zero((unsigned int) MAXIMUM);
  for (int i = 0; i < max_show; ++i)
  {
    int index = 1 << i;
    std::pair<double, double> p = insert_by_index_results[index - 1];
    std::cout << "Index: " << index - 1 << "\t" << (p.first / p.second) << "\t" << (p.second / p.first) << "\tLogNVector: " << p.first << "\tstd::vector: " << p.second << std::endl;
    p = insert_by_index_results[index];
    std::cout << "Index: " << index << "\t" << (p.first / p.second) << "\t" << (p.second / p.first) << "\tLogNVector: " << p.first << "\tstd::vector: " << p.second << std::endl;
    p = insert_by_index_results[index + 1];
    std::cout << "Index: " << index + 1 << "\t" << (p.first / p.second) << "\t" << (p.second / p.first) << "\tLogNVector: " << p.first << "\tstd::vector: " << p.second << std::endl;
  }

  // index insertion csv
    std::cout << "index,log_vector/std_vector,std_vector/log_vector,log_vector,std_vector\n";
  for (int i = 0; i < MAXIMUM; ++i)
  {
    std::pair<double, double> p = insert_by_index_results[i];
    std::cout << i << "," << (p.first / p.second) << "," << (p.second / p.first) << "," << p.first << "," << p.second << std::endl;
  }
 */