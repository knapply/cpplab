#ifndef __KNAPPLY__COMMON_HPP__
#define __KNAPPLY__COMMON_HPP__


#include "portability.hpp"
#include "stl-compat.hpp"


#include <array>
#include <limits>
#include <string_view>
#include <vector>


namespace knapply {

template <class int_T>
constexpr bool is_min(const int_T x) {
  return x == std::numeric_limits<int_T>::min();
}


template <class T, class U>
constexpr bool is_same_ish_v = std::is_same_v<std::remove_cvref<T>, std::remove_cvref<U>>;


template <class T>
constexpr bool is_char_ish_v = (std::is_same_v<T, char> ||
                                std::is_same_v<T, unsigned char> ||
                                std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>
#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
                                || std::is_same_v<T, char8_t>
#endif
);


} // namespace knapply


#endif
