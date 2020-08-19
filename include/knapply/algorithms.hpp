#ifndef __KNAPPLY__ALGOTITHMS_HPP__
#define __KNAPPLY__ALGOTITHMS_HPP__

#include <array>
#include <algorithm>
#include <iterator> /* std::size */


namespace knapply {


template <typename container_T, typename predicate_T>
inline constexpr bool all_are(const container_T& c, predicate_T p) {
  for (auto it = std::cbegin(c); it != std::cend(c); ++it) {
    if (!p(*it)) {
      return false;
    }
  }
  return true;
}


template <typename container_T, typename predicate_T>
inline constexpr bool none_are(const container_T& c, predicate_T p) {
  for (auto it = std::cbegin(c); it != std::cend(c); ++it) {
    if (p(*it)) {
      return false;
    }
  }
  return true;
}


template <typename container_T, typename target_T>
inline constexpr std::size_t count(const container_T& c, target_T t) {
  std::size_t out = 0;
  for (auto it = std::cbegin(c); it != std::cend(c); ++it) {
    if (*it == t) {
      out++;
    }
  }
  return out;
}
constexpr std::array<int, 6> count_tester{1, 0, 1, 2, 1, 2};
static_assert(count(count_tester, 0) == 1);
static_assert(count(count_tester, 1) == 3);
static_assert(count(count_tester, 2) == 2);
static_assert(count(count_tester, -1) == 0);


// template <typename container_T, typename predicate_T>
// inline constexpr auto which_is_not(const container_T& c, predicate_T p) {
//   const auto n = std::size(c);
//   for (std::size_t i = 0; i < n; ++i) {
//     if (!p(c[i])) {
//       return i;
//     }
//   }
//   return n;
// }


} // namespace knapply


#endif
