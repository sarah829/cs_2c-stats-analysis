#include <iostream>
#include <vector>

#include "log_n_vector.h"

using std::cout;
using std::endl;

int main() {
  LogNVector<int> v = {0, 11, 22, 33, 44, 55, 66, 77, 88, 99, 110, 121};
  cout << "v[0] == " << v[0] << ",    &v[0] == " << &v[0] << endl;
  for (int j = 1; j < v.size(); ++j) {
    // All the elements in a single array should have sequential addresses.
    // For example, &v[2] == &v[1] + 1
    // However, there's no guarantee that &v[1] == &v[0] + 1.
    cout << "v[" << j << "] == " << v[j] << ",    "
         << "&v[" << j << "] - &v[" << j - 1 << "] == "
         << &v[j] - &v[j - 1] << endl;
  }

  LogNVector<int> v1(v);
  v1[0] = 50;
  cout << "v1[0] == " << v1[0] << ",    &v1[0] == " << &v1[0] << endl;
  for (int j = 1; j < v1.size(); ++j) {
    // All the elements in a single array should have sequential addresses.
    // For example, &v1[2] == &v1[1] + 1
    // However, there's no guarantee that &v1[1] == &v1[0] + 1.
    cout << "v1[" << j << "] == " << v1[j] << ",    "
         << "&v1[" << j << "] - &v1[" << j - 1 << "] == "
         << &v1[j] - &v1[j - 1] << endl;
  }
  std::vector<int> testing;
  testing.push_back(55);
  testing.pop_back();
  return 0;
}