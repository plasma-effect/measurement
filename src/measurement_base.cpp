#include "measurement-base.hpp"
#include <iostream>
using namespace std::chrono;

namespace measurement {
std::vector<std::unique_ptr<Measure>> Measure::measures;
void Measure::Start() {
  stopped = false;
  start_ = system_clock::now();
}
void Measure::Stop() {
  end_ = system_clock::now();
  stopped = true;
}
microseconds Measure::ExecuteMeasure() {
  Start();
  MeasureBody();
  if (!stopped) [[likely]] {
    Stop();
  }
  return duration_cast<microseconds>(end_ - start_);
}

void* Measure::RegistorMeasurement(std::unique_ptr<Measure>&& ptr) {
  measures.push_back(std::move(ptr));
  return nullptr;
}
void Measure::ExecuteAll(int count) {
  for (auto& m_ptr : measures) {
    for (int c = 0; c < count; ++c) {
      auto elapsed_us = m_ptr->ExecuteMeasure();
      std::cout << m_ptr->GetSuiteName() << "," << m_ptr->GetName() << ","
                << elapsed_us.count() << std::endl;
    }
  }
}
} // namespace measurement
