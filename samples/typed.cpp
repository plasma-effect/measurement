#include "measurement.hpp"
#include <random>

template <typename Engine> class RandomEngine : public ::measurement::Measure {
protected:
  std::uniform_int_distribution<int> dist{1, 15};
};

using types =
    ::measurement::Types<std::minstd_rand, std::mt19937, std::ranlux24>;
TYPED_MEASURE_SUITE(RandomEngine, types);

TYPED_MEASURE(RandomEngine, Sum) {
  TypeParam engine;
  int sum = 0;
  Start();
  for (int i = 0; i < 10000; ++i) {
    sum += TestFixture::dist(engine);
  }
  Stop();
  MEASURE_DUMMY(sum);
}

TYPED_MEASURE(RandomEngine, Xor) {
  TypeParam engine;
  int sum = 0;
  Start();
  for (int i = 0; i < 10000; ++i) {
    sum ^= TestFixture::dist(engine);
  }
  Stop();
  MEASURE_DUMMY(sum);
}
