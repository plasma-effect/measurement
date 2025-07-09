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
template <typename... Ts> struct ConcatTypeListBase;
template <typename... Ts0, typename... Ts1, typename... Ts2>
struct ConcatTypeListBase<Types<Ts0...>, Types<Ts1...>, Ts2...> {
  using type = typename ConcatTypeListBase<Types<Ts0..., Ts1...>, Ts2...>::type;
};
template <typename T> struct ConcatTypeListBase<T> {
  using type = typename GenerateTypeListBase<T>::type;
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
template <typename... Ts>
using ConcatTypeList = typename internal::ConcatTypeListBase<Ts...>;
} // namespace measurement
