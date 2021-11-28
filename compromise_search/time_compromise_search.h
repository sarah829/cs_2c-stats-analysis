/*
  File name: time_compromise_search.h
  @version1.0 2021-09-26
  @author Sarah Youngquist
  Program Purpose: header file for time_compromise_search.cpp
    Defines functions to time compromise search, std::find, and std::binary_search
  For Foothill College Class: F21 CS F002C Data Structures and Algorithms in C++
  Homework 1B, due 2021-09-27
 */

#ifndef TIME_COMPROMISE_SEARCH_H_
#define TIME_COMPROMISE_SEARCH_H_
// *************************************************************************************************
// struct to easily make a min heap comparing two pairs by first in decreasing order
struct compare_pair_heap {
  bool operator()(const std::pair<int, double> &pair1, const std::pair<int, double> &pair2) {
    return pair1.second > pair2.second;
  }
};
// *************************************************************************************************
// functions for displaying results ----------------------------------------------------------------

// format good for csv
void results_test_small_sizes_and_sizes();

// displays the results sorted by small_size then size given small_sizes
void display_test_small_sizes_and_sizes();

// for testing all small_sizes for powers of 2
void results_for_all_small_sizes();

// functions for testing ---------------------------------------------------------------------------
/*
  this function tests many sizes for a given list of small sizes. it is meant to get data to
  compare different small_sizes.
  results are stored in tuples (small_size, size, time). results are returned as a set so that they
  are sorted first by small_size, then size
 */
std::set<std::tuple<int, int, double>> test_small_sizes_and_sizes(int trials, int reps, int max_size, int max_small_size, double size_multiplier, double small_size_multiplier);

/*
  this is the function used to compare_pair times between the three different search methods
  returns a vector of 3 priority queues of pairs of <time, small_size>, 1 for each search type
  they are in the order 0: compromise_search, 1: std::find, 2: std::binary_search
  the latter two priority queues only have 1 element since small_size doesn't matter
  values is a vector that is to be searched
  sample_size is how many items from it should be randomly chosen to search for
  trials is the number of different samples that should be taken
  reps is the number of times each of those trials is tested
  min_ and max_ small_size denote the range of values for small_size that should be tested
 */
template<class T>
std::vector<std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, compare_pair_heap>> test_size(
    const std::vector<T> &values,
    int sample_size,
    int trials,
    int reps,
    int min_small_size,
    int max_small_size);

// helper functions --------------------------------------------------------------------------------
/*
  returns the time it takes to search values for all of the elements in sample_values with the
  given small_size using compromise search
 */
template<class T>
double time_compromise(const std::vector<T> &values,
    const std::vector<T> &sample_values,
    int small_size);

/*
  returns the time it takes to search values for all of the elements in sample_values using
  std::find, a linear search
*/
template<class T>
double time_std_find(const std::vector<T> &values, const std::vector<T> &sample_values);

/*
  returns the time it takes to search values for all of the elements in sample_values using
  std::binary_search
*/
template<class T>
double time_std_binary(const std::vector<T> &values, const std::vector<T> &sample_values);

/*
  generates a random sample with sample_size elements from values and returns a vector.
  there can be duplicates
*/
template<class T>
std::vector<T> random_sample(const std::vector<T> &values, int sample_size);

#endif //TIME_COMPROMISE_SEARCH_H_
