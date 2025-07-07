#include "measurement-base.hpp"
#include <iostream>
using namespace std::chrono;

namespace {
using measure_ptr = std::unique_ptr<measurement::Measure>;
std::vector<std::tuple<const char*, const char*, int, measure_ptr>> measures;
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
void* RegisterMeasurement(const char* suite_name, const char* name, int index,
                          std::unique_ptr<Measure>&& ptr) {
  measures.emplace_back(suite_name, name, index, std::move(ptr));
  return nullptr;
}
void ExecuteAll(int count) {
  for (auto& [sname, name, idx, m_ptr] : measures) {
    for (int c = 0; c < count; ++c) {
      auto elapsed_us = m_ptr->ExecuteMeasure();
      std::cout << sname << "," << name << "," << idx << ","
                << elapsed_us.count() << std::endl;
    }
  }
}
} // namespace measurement
