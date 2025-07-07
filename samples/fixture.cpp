#include "measurement.hpp"
#include <random>

class FixtureTest : public ::measurement::Measure {
  static inline std::mt19937 engine;

protected:
  std::vector<int> vec;
  void SetUp() override {
    std::uniform_int_distribution dist(1, 15);
    vec.resize(10000);
    for (auto& v : vec) {
      v = dist(engine);
    }
  }
};

MEASURE_F(FixtureTest, VectorSum) {
  int sum = 0;
  for (auto v : vec) {
    sum += v;
  }
  MEASURE_DUMMY(sum);
}

MEASURE_F(FixtureTest, VectorXor) {
  int sum = 0;
  for (auto v : vec) {
    sum ^= v;
  }
  MEASURE_DUMMY(sum);
}
