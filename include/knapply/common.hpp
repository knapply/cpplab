#ifndef __KNAPPLY__COMMON_HPP__
#define __KNAPPLY__COMMON_HPP__

#include "stl-compat.hpp"
#include <limits>


namespace knapply {

template <class int_T>
inline constexpr bool is_min(const int_T x) {
  return x == std::numeric_limits<int_T>::min();
}


} // namespace knapply


#endif
