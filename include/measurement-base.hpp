#pragma once
#include "internal/preprocessor.hpp"
#include <chrono>
#include <memory>
#include <vector>

namespace measurement {
class Measure {
  const char* suite_name_;
  const char* name_;
  int index_;
  std::chrono::system_clock::time_point start_ = {}, end_ = {};
  bool stopped = false;
  static std::vector<std::unique_ptr<Measure>> measures;

protected:
  Measure(const char* suite_name, const char* name, int index)
      : suite_name_(suite_name), name_(name), index_(index) {}
  virtual void MeasureBody() = 0;
  virtual void SetUp() {}    // do nothing
  virtual void TearDown() {} // do nothing
  void Start();
  void Stop();

public:
  Measure(const Measure&) = delete;
  Measure& operator=(const Measure&) = delete;
  Measure(Measure&&) = delete;
  Measure& operator=(Measure&&) = delete;
  virtual ~Measure() = default;

  virtual std::chrono::microseconds ExecuteMeasure();
  const char* GetSuiteName() const {
    return suite_name_;
  }
  const char* GetName() const {
    return name_;
  }
  int GetIndex() const {
    return index_;
  }

  static void* RegistorMeasurement(std::unique_ptr<Measure>&& ptr);
  static void ExecuteAll(int count);
};
} // namespace measurement

#define MEASURE_CONSTRUCT(suite_name, name, class_name, parent_name)           \
  class class_name : public parent_name {                                      \
  public:                                                                      \
    class_name() : parent_name(#suite_name, #name, 0) {}                       \
                                                                               \
  protected:                                                                   \
    virtual void MeasureBody() override;                                       \
  };                                                                           \
  void* MEASURE_PP_CAT(class_name, test_info) =                                \
      ::measurement::Measure::RegistorMeasurement(                             \
          std::make_unique<class_name>());                                     \
  void class_name::MeasureBody()

#define MEASURE(suite_name, name)                                              \
  MEASURE_CONSTRUCT(suite_name, name, MEASURE_PP_CAT(suite_name, name),        \
                    ::measurement::Measure)
