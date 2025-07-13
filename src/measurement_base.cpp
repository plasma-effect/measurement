#include "measurement-base.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <tuple>
using namespace std::chrono;

namespace {
using measure_ptr = std::unique_ptr<measurement::Measure>;
std::vector<std::tuple<std::array<std::string, 3>, measure_ptr>> measures;
} // namespace

namespace measurement {
void Measure::Start() {
  stopped = false;
  start_ = system_clock::now();
}
void Measure::Stop() {
  end_ = system_clock::now();
  stopped = true;
}
microseconds Measure::ExecuteMeasure() {
  SetUp();
  Start();
  MeasureBody();
  if (!stopped) [[likely]] {
    Stop();
  }
  TearDown();
  return duration_cast<microseconds>(end_ - start_);
}
void* RegisterMeasurement(std::string suite_name, std::string name,
                          std::string param, std::unique_ptr<Measure>&& ptr) {
  measures.emplace_back(
      std::array{std::move(suite_name), std::move(name), std::move(param)},
      std::move(ptr));
  return nullptr;
}
void ExecuteAll(int count) {
  for (auto& [names, m_ptr] : measures) {
    for (int c = 0; c < count; ++c) {
      auto elapsed_us = m_ptr->ExecuteMeasure();
      std::cout << names[0] << "," << names[1] << "," << names[2] << ","
                << elapsed_us.count() << std::endl;
    }
  }
}
} // namespace measurement
