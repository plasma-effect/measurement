#pragma once
#include "internal/preprocessor.hpp"
#include <chrono>
#include <memory>
#include <vector>

namespace measurement {
class Measure {
  std::chrono::system_clock::time_point start_ = {}, end_ = {};
  bool stopped = false;

protected:
  virtual void MeasureBody() = 0;
  virtual void SetUp() {}    // do nothing
  virtual void TearDown() {} // do nothing
  void Start();
  void Stop();

public:
  Measure() = default;
  Measure(const Measure&) = delete;
  Measure& operator=(const Measure&) = delete;
  Measure(Measure&&) = delete;
  Measure& operator=(Measure&&) = delete;
  virtual ~Measure() = default;

  virtual std::chrono::microseconds ExecuteMeasure();
};
void* RegisterMeasurement(const char* suite_name, const char* name,
                          std::size_t index, std::unique_ptr<Measure>&& ptr);
void ExecuteAll(int count);
} // namespace measurement

#define MEASURE_SUITE_NAME(suite_name, name)                                   \
  MEASURE_PP_CAT5(suite_name, _, name, _, Measure)

#define MEASURE_CONSTRUCT(suite_name, name, class_name, parent_name)           \
  static_assert(sizeof(MEASURE_PP_STR(suite_name)) > 1,                        \
                "suite_name must not be empty");                               \
  static_assert(sizeof(MEASURE_PP_STR(name)) > 1, "name must not be empty");   \
  class class_name : public parent_name {                                      \
  public:                                                                      \
    class_name() = default;                                                    \
                                                                               \
  protected:                                                                   \
    virtual void MeasureBody() override;                                       \
  };                                                                           \
  static void* MEASURE_PP_CAT(class_name, _registered) =                       \
      ::measurement::RegisterMeasurement(MEASURE_PP_STR(suite_name),           \
                                         MEASURE_PP_STR(name), 0,              \
                                         std::make_unique<class_name>());      \
  void class_name::MeasureBody()

#define MEASURE(suite_name, name)                                              \
  MEASURE_CONSTRUCT(suite_name, name, MEASURE_SUITE_NAME(suite_name, name),    \
                    ::measurement::Measure)
