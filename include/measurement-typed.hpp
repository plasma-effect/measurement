#pragma once
#include "internal/type-utils.hpp"
#include "measurement-base.hpp"

namespace measurement::internal {
template <template <typename> typename TestFixture, typename Head,
          typename Tails>
struct TypeParameterizedMeasure {
  static void* RegisterMeasurement(const char* suite_name, const char* name,
                                   std::size_t index) {
    ::measurement::RegisterMeasurement(suite_name, name, index,
                                       std::make_unique<TestFixture<Head>>());
    return TypeParameterizedMeasure<
        TestFixture, typename Tails::Head,
        typename Tails::Tails>::RegisterMeasurement(suite_name, name,
                                                    index + 1);
  }
};
template <template <typename> typename TestFixture>
struct TypeParameterizedMeasure<TestFixture, Null, Types<>> {
  static void* RegisterMeasurement(const char*, const char*, std::size_t) {
    return nullptr;
  }
};
} // namespace measurement::internal

#define TYPE_PARAMS_NAME(suite_name)                                           \
  MEASURE_PP_CAT(plasma_measure_type_params_, suite_name)

#define TYPED_MEASURE_SUITE(suite_name, types)                                 \
  using TYPE_PARAMS_NAME(suite_name) = ::measurement::GenerateTypeList<types>;

#define TYPED_MEASURE_CONSTRUCT(suite_name, name, class_tpl, parent_tpl)       \
  static_assert(sizeof(MEASURE_PP_STR(name)) > 1, "name must not be empty");   \
  template <typename T> class class_tpl : public parent_tpl<T> {               \
  public:                                                                      \
    class_tpl() = default;                                                     \
                                                                               \
  protected:                                                                   \
    using TestFixture = parent_tpl<T>;                                         \
    using TypeParam = T;                                                       \
    virtual void MeasureBody() override;                                       \
    void Start() {                                                             \
      ::measurement::Measure::Start();                                         \
    }                                                                          \
    void Stop() {                                                              \
      ::measurement::Measure::Stop();                                          \
    }                                                                          \
  };                                                                           \
  static void* MEASURE_PP_CAT(class_tpl, _registered) =                        \
      ::measurement::internal::TypeParameterizedMeasure<                       \
          class_tpl, typename TYPE_PARAMS_NAME(suite_name)::Head,              \
          typename TYPE_PARAMS_NAME(suite_name)::Tails>::                      \
          RegisterMeasurement(MEASURE_PP_STR(suite_name),                      \
                              MEASURE_PP_STR(name), 0);                        \
  template <typename measure_tpl_param>                                        \
  void class_tpl<measure_tpl_param>::MeasureBody()

#define TYPED_MEASURE(suite_name, name)                                        \
  TYPED_MEASURE_CONSTRUCT(suite_name, name,                                    \
                          MEASURE_SUITE_NAME(suite_name, name), suite_name)
