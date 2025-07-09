#include "measurement.hpp"
#include <random>

template <typename Engine>
class NamedRandomEngine : public ::measurement::Measure {
protected:
  std::uniform_int_distribution<int> dist{1, 15};
};

struct Selector {
  template <typename Engine> static std::string GetName(std::size_t) {
    if constexpr (std::is_same_v<Engine, std::minstd_rand>) {
      return "std::minstd_rand";
    } else if constexpr (std::is_same_v<Engine, std::mt19937>) {
      return "std::mt19937";
    } else if constexpr (std::is_same_v<Engine, std::ranlux24>) {
      return "std::ranlux24";
    }
  }
};

using types =
    ::measurement::Types<std::minstd_rand, std::mt19937, std::ranlux24>;
TYPED_MEASURE_SUITE(NamedRandomEngine, types, Selector);

TYPED_MEASURE(NamedRandomEngine, Sum) {
  TypeParam engine;
  int sum = 0;
  Start();
  for (int i = 0; i < 10000; ++i) {
    sum += TestFixture::dist(engine);
  }
  Stop();
  MEASURE_DUMMY(sum);
}

TYPED_MEASURE(NamedRandomEngine, Xor) {
  TypeParam engine;
  int sum = 0;
  Start();
  for (int i = 0; i < 10000; ++i) {
    sum ^= TestFixture::dist(engine);
  }
  Stop();
  MEASURE_DUMMY(sum);
}
