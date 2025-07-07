#pragma once
#include "internal/type-utils.hpp"
#include "measurement-base.hpp"

namespace measurement::internal {
template <template <typename> typename TestFixture, typename Head,
          typename Tails>
struct TypeParameterizedMeasure {
  static void* RegistorMeasurement(const char* suite_name, const char* name,
                                   std::size_t index) {
    ::measurement::RegistorMeasurement(suite_name, name, index,
                                       std::make_unique<TestFixture<Head>>());
    return TypeParameterizedMeasure<
        TestFixture, typename Tails::Head,
        typename Tails::Tails>::RegistorMeasurement(suite_name, name,
                                                    index + 1);
  }
};
template <template <typename> typename TestFixture>
struct TypeParameterizedMeasure<TestFixture, Null, Types<>> {
  static void* RegistorMeasurement(const char* suite_name, const char* name,
                                   std::size_t index) {
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
  };                                                                           \
  static void* MEASURE_PP_CAT(class_tpl, test_info) =                          \
      ::measurement::internal::TypeParameterizedMeasure<                       \
          class_tpl, typename TYPE_PARAMS_NAME(suite_name)::Head,              \
          typename TYPE_PARAMS_NAME(suite_name)::Tails>::                      \
          RegistorMeasurement(MEASURE_PP_STR(suite_name),                      \
                              MEASURE_PP_STR(name), 0);                        \
  template <typename T> void class_tpl<T>::MeasureBody()

#define TYPED_MEASURE(suite_name, name)                                        \
  TYPED_MEASURE_CONSTRUCT(suite_name, name, MEASURE_PP_CAT(suite_name, name),  \
                          suite_name)
