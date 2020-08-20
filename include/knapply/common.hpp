#ifndef __KNAPPLY__COMMON_HPP__
#define __KNAPPLY__COMMON_HPP__


#include "portability.hpp"
#include "stl-compat.hpp"
#include <limits>


namespace knapply {

template <class int_T>
inline constexpr bool is_min(const int_T x) {
  return x == std::numeric_limits<int_T>::min();
}


template <class T, class U>
inline constexpr bool is_sameish_v =
    std::is_same_v<std::remove_cvref<T>, std::remove_cvref<U>>;


} // namespace knapply


#endif
