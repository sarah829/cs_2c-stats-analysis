/*
 * File name: compromise_search.h
 * @author Sarah Youngquist
 * Program Purpose: Implements compromise search, which combines binary and linear search
 *  depending on list size.
 * Notes:
 *  Uses binary search until high - low <= small_size
 *  RandomAccessIt is a random-access iterator, and T is any class that defines < and ==.
 * For Foothill College Class: F21 CS F002C Data Structures and Algorithms in C++
 * Homework 1, due 2021-09-27
 */

template<class RandomAccessIt, class T>
RandomAccessIt compromise_search(RandomAccessIt low, RandomAccessIt high, const T& value, int small_size)
{
  // redacted because homework assignment
}