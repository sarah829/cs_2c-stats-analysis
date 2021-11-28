/*
  File name: time_compromise_search.cpp
  @version1.0 2021-09-19
  @author Sarah Youngquist
  Program Purpose: Implements functions to time compromise search, std::find, and std::binary_search
    prints data in a format that can easily be directed to a csv file
  For Foothill College Class: F21 CS F002C Data Structures and Algorithms in C++
  Homework 1B, due 2021-09-27
 */

#include <iostream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <random>

#include <queue>
#include <vector>
#include <set>
#include <utility>
#include <tuple>
#include <iterator>

#include "compromise_search.h"
#include "time_compromise_search.h"

// constants (so that I can change them easily during testing)
// for test_size all small sizes
const int MAX_SIZE_TEST_ALL = 256; // goes up by powers of 2
const int MAX_SHOWN = 100;
// both
const int TRIALS = 5;
const int REPS = 10;
// for test_small_sizes_and_sizes some small sizes
const int SAMPLE_SIZE_FRACTION = 10;
const double SIZE_MULTIPLIER = 1.04;
const double SMALL_SIZE_MULTIPLIER = 1.1;
const int MAX_SIZE = 200000;
const int MAX_SMALL_SIZE = 250;
// -------------------------------------------------------------------------------------------------
// main
int main() {
  results_test_small_sizes_and_sizes();
}

// *************************************************************************************************
// function definitions

// functions for showing results -------------------------------------------------------------------
// results of test_small_sizes_and_sizes, intended for csv
void results_test_small_sizes_and_sizes()
{
  std::cout.precision(std::numeric_limits<double>::max_digits10 - 1);
  std::set<std::tuple<int, int, double>> results = test_small_sizes_and_sizes(TRIALS, REPS, MAX_SIZE, MAX_SMALL_SIZE, SIZE_MULTIPLIER, SMALL_SIZE_MULTIPLIER);
  std::cout << "small_size,size,time\n";
  for (auto elem : results)
  {
    std::cout << std::get<0>(elem) << "," << std::get<1>(elem) << "," << std::get<2>(elem) << std::endl;
  }
}

// pretty display of test_small_sizes_and_sizes (not for raw data)
void display_test_small_sizes_and_sizes()
{
  std::cout.precision(std::numeric_limits<double>::max_digits10 - 1);
  std::set<std::tuple<int, int, double>> results =
      test_small_sizes_and_sizes(TRIALS, REPS, MAX_SIZE, MAX_SMALL_SIZE, SIZE_MULTIPLIER, SMALL_SIZE_MULTIPLIER);
  std::cout << "------ std::find linear search ------\n"; // starts w/ linear
  int small_size = -2;
  for (auto elem : results)
  {
    if (std::get<0>(elem) != small_size)
    {
      small_size = std::get<0>(elem);
      if (small_size == -1)
      {
        std::cout << "------ std::binary_search  ------\n";
      }
      else {
        std::cout << "------ small size: " << small_size << " ------\n";
      }
    }
    std::cout << " size: " << std::get<1>(elem) << ", time: " << std::get<2>(elem) << std::endl;
  }
}

// iterates through small sizes and only tests powers of two
void results_for_all_small_sizes() {
  // vector of the priority queues of results. each element is for a different list size
  // the size is 2^i where i is the index
  std::vector<std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, compare_pair_heap>> compromise_results;
  std::vector<double> std_find_results;
  std::vector<double> std_binary_results;
  std::vector<int> sizes;
  // get results for each size

  for (int n = 1; n <= MAX_SIZE_TEST_ALL; n *= 2) {
    sizes.push_back(n);
    // generate the values
    std::vector<int> values;
    values.reserve(n);
    for (int j = 0; j < n; ++j) {
      values.push_back(j);
    }

    std::vector<std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, compare_pair_heap>> results;
    results = test_size(values, n / SAMPLE_SIZE_FRACTION + 1, TRIALS, REPS, 0, n);
    compromise_results.push_back(results[0]);
    std_find_results.push_back(results[1].top().second);
    std_binary_results.push_back(results[2].top().second);
  }

  int number_of_sizes = int(sizes.size());

  std::cout.precision(std::numeric_limits<double>::max_digits10 - 1);
  // Show results good for CSV types: f is linear find, b is binary, c is compromise
  std::cout << "size,type,time,small_size\n";
  for (int n = 0; n < number_of_sizes; n++) {
    // show results from std
    std::cout << sizes[n] << "," << "f," << std_find_results[n] << std::endl
              << sizes[n] << "," << "b," << std_binary_results[n] << std::endl;

    // compromise search results
    std::pair<int, double> pair;
    int num_results = std::min(sizes[n], 10);
    for (int i = 0; i <= num_results; i++) {
      pair = compromise_results[n].top();
      compromise_results[n].pop();
      std::cout << sizes[n] << "," << "c," << pair.second << "," << pair.first << std::endl;
    }
  }
}

// functions for testing ---------------------------------------------------------------------------
std::set<std::tuple<int, int, double>> test_small_sizes_and_sizes(int trials, int reps, int max_size, int max_small_size, double size_multiplier, double small_size_multiplier)
{
  std::set<std::tuple<int, int, double>> results;
  int size = 1;
  std::vector<int> values;
  values.push_back(0);
  while (size <= max_size)
  {
    // get random samples
    int sample_size = size / SAMPLE_SIZE_FRACTION + 1;
    std::vector<std::vector<int>> samples;
    samples.reserve(trials);
    for (int i = 0; i < trials; ++i) {
      samples.push_back(random_sample(values, sample_size));
    }
    int small_size = 0;
    while (small_size <= max_small_size)
    {
      //if (small_size <= size) // stop when small_size too big (small_sizes must be sorted)
      {
        // iterate through samples
        double compromise_time = 0;
        for (const std::vector<int> &sample : samples) {
          // do each trial reps times
          for (int i = 0; i < reps; ++i) {
            compromise_time += time_compromise(values, sample, small_size);
          }
        }
        // avg time
        compromise_time /= (trials * reps * sample_size);
        results.insert(std::tuple<int, int, double>(small_size, size, compromise_time));
      }
      /*
      else {
        break;
      }
       */
      small_size = floor(small_size_multiplier * small_size + 1);
    }

    // std::find and std::binary
    double std_find_time = 0, std_binary_time = 0;
    for (const std::vector<int> &sample : samples) {
      // do each trial reps times
      for (int i = 0; i < reps; ++i) {
        std_binary_time += time_std_binary(values, sample);
        std_find_time += time_std_find(values, sample);
      }
    }
    // avg time
    std_binary_time /= (trials * reps * sample_size);
    std_find_time /= (trials * reps * sample_size);
    results.insert(std::tuple<int, int, double>(-1, size, std_binary_time));
    results.insert(std::tuple<int, int, double>(-2, size, std_find_time));

    // add numbers to values
    int current_size = size;
    size = ceil(size_multiplier * size);
    for (int i = current_size; i < size; i++)
    {
      values.push_back(i);
    }
  }
  return results;
}

template<class T>
std::vector<std::priority_queue<std::pair<int, double>,
                                std::vector<std::pair<int, double>>,
                                compare_pair_heap>> test_size(const std::vector<T> &values,
    int sample_size,
    int trials,
    int reps,
    int min_small_size,
    int max_small_size) {
  // store results
  std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, compare_pair_heap> compromise_time_pairs;
  // these two only have 1 element since they don't care about small_size
  // necessary b/c need to use the same random samples
  std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, compare_pair_heap> std_find_time_pairs;
  std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, compare_pair_heap> std_binary_time_pairs;

  std::vector<std::vector<T>>
      samples; // stores a vector of the random samples (size will be trials)

  // get the random samples
  samples.reserve(trials);
  for (int i = 0; i < trials; ++i) {
    samples.push_back(random_sample(values, sample_size));
  }

  // test_size compromise search
  // iterate through small_size values
  for (int small_size = min_small_size; small_size <= max_small_size; ++small_size) {
    double compromise_time = 0.0;
    // iterate through samples
    for (const std::vector<T> &sample : samples) {
      // do each trial reps times
      for (int i = 0; i < reps; ++i) {
        compromise_time += time_compromise(values, sample, small_size);
      }
    }
    // avg time
    compromise_time /= (trials * reps * sample_size);
    compromise_time_pairs.push(std::pair<int, double>(small_size, compromise_time));
  }

  // test_size std::find and std::binary_search
  double std_find_time = 0.0, std_binary_time = 0;
  // iterate through samples
  for (const std::vector<T> &sample : samples) {
    // do each trial reps times
    for (int i = 0; i < reps; ++i) {
      std_find_time += time_std_find(values, sample);
      std_binary_time += time_std_binary(values, sample);
    }
  }
  // avg time
  std_find_time /= (trials * reps * sample_size);
  std_binary_time /= (trials * reps * sample_size);
  std_find_time_pairs.push(std::pair<int, double>(-1, std_find_time));
  std_binary_time_pairs.push(std::pair<int, double>(-2, std_binary_time));

  // return results
  std::vector<std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, compare_pair_heap>> results;
  results.push_back(compromise_time_pairs);
  results.push_back(std_find_time_pairs);
  results.push_back(std_binary_time_pairs);
  return results;
}

// helper functions --------------------------------------------------------------------------------
template<class T>
double time_compromise(const std::vector<T> &values,
    const std::vector<T> &sample_values,
    int small_size) {
  auto start = std::chrono::steady_clock::now();
  for (const T &t : sample_values) {
    compromise_search(values.begin(), values.end(), t, small_size);
  }
  auto stop = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = stop - start;
  return elapsed.count();
}

template<class T>
double time_std_find(const std::vector<T> &values, const std::vector<T> &sample_values) {
  auto start = std::chrono::steady_clock::now();
  for (const T &t : sample_values) {
    std::find(values.begin(), values.end(), t);
  }
  auto stop = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = stop - start;
  return elapsed.count();
}

template<class T>
double time_std_binary(const std::vector<T> &values, const std::vector<T> &sample_values) {
  auto start = std::chrono::steady_clock::now();
  for (const T &t : sample_values) {
    std::binary_search(values.begin(), values.end(), t);
  }
  auto stop = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = stop - start;
  return elapsed.count();
}

template<class T>
std::vector<T> random_sample(const std::vector<T> &values, int sample_size) {
  std::random_device rd;
  std::uniform_int_distribution<int> uniform_dist(0, values.size() - 1);
  std::vector<T> sample;
  sample.reserve(sample_size);
  for (int i = 0; i < sample_size; ++i) {
    sample.push_back(values[uniform_dist(rd)]);
  }
  return sample;
}