#include "measurement.hpp"
#include <random>

template <typename Engine>
class RandomEngine : public ::measurement::Measure {};

using types =
    ::measurement::Types<std::minstd_rand, std::mt19937, std::ranlux24>;
TYPED_MEASURE_SUITE(RandomEngine, types);

TYPED_MEASURE(RandomEngine, Sum) {
  TypeParam engine;
  std::uniform_int_distribution<int> dist(1, 15);
  int sum = 0;
  for (int i = 0; i < 10000; ++i) {
    sum += dist(engine);
  }
  MEASURE_DUMMY(sum);
}

TYPED_MEASURE(RandomEngine, Xor) {
  TypeParam engine;
  std::uniform_int_distribution<int> dist(1, 15);
  int sum = 0;
  for (int i = 0; i < 10000; ++i) {
    sum ^= dist(engine);
  }
  MEASURE_DUMMY(sum);
}
