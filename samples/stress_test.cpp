#include "measurement.hpp"
#include <algorithm>
#include <iostream>
#include <malloc.h>
#include <numeric>
#include <random>
#include <utility>

template <typename Indexes> struct MakeStressTestImpl;
template <std::size_t... Is>
struct MakeStressTestImpl<std::index_sequence<Is...>> {
  using type = ::measurement::Types<std::integral_constant<std::size_t, Is>...>;
};
template <std::size_t Size> struct MakeStressTest {
  using type =
      typename MakeStressTestImpl<std::make_index_sequence<Size>>::type;
};
using types = typename MakeStressTest<500>::type;

template <typename T> class StressTest : public ::measurement::Measure {
protected:
  std::mt19937 engine{T::value};
  std::unique_ptr<int[]> vec;

  void SetUp() override {
    vec = std::make_unique<int[]>(100'000);
    std::iota(vec.get(), vec.get() + 100'000, 0);
    std::shuffle(vec.get(), vec.get() + 100'000, engine);
  }
  void TearDown() override {
    auto mi = mallinfo2();
    std::cerr << "total allocated space (arena): " << mi.arena << " bytes\n";
    std::cerr << "total allocated via malloc: " << mi.uordblks << " bytes\n";
    std::cerr << std::flush;
  }
};

TYPED_MEASURE_SUITE(StressTest, types);

TYPED_MEASURE(StressTest, Run) {
  int sum = 0;
  for (int i = 0; i < 100'000; ++i) {
    sum += TestFixture::vec[i];
  }
  MEASURE_DUMMY(sum);
}
