/*
  File name: log_n_vector.h
  @author Sarah Youngquist
  Program Purpose: Defines class LogNVector, which is a std::vector of arrays.
    It functions like a vector except that when push_back is called, elements
    are not copied. Instead, another array is added with size twice as big as
    the previous.
 * For Foothill College Class: F21 CS F002C Data Structures and Algorithms in C++
 * Homework 2 O(log(N)) Vector Due 2021-10-04
 */

#ifndef _log_n_vector_h_
#define _log_n_vector_h_

#include <cmath>
#include <bit>
#include <memory>
#include <vector>
#include <utility>

template <typename T>
class LogNVector {
  // redacted because homework assignment
};

#endif // _log_n_vector_h_