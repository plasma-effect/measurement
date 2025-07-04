#include "measurement.hpp"
#include <vector>

MEASURE(Simple, VectorSum) {
  std::vector<int> vec;
  for (int i = 0; i < 10000; ++i) {
    vec.emplace_back(i);
  }
  int sum = 0;
  for (auto v : vec) {
    sum += v;
  }
  MEASURE_DUMMY(sum);
}
