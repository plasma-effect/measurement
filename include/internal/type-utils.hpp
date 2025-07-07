#pragma once

namespace measurement {
template <typename...> struct Types;
namespace internal {
struct Null {};
template <typename T> struct GenerateTypeListBase {
  using type = Types<T>;
};
template <typename... Ts> struct GenerateTypeListBase<Types<Ts...>> {
  using type = Types<Ts...>;
};
} // namespace internal
template <typename T, typename... Ts> struct Types<T, Ts...> {
  using Head = T;
  using Tails = Types<Ts...>;
};
template <> struct Types<> {
  using Head = internal::Null;
  using Tails = Types<>;
};
template <typename T>
using GenerateTypeList = typename internal::GenerateTypeListBase<T>::type;
} // namespace measurement
