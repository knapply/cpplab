#ifndef __KNAPPLY__STL_COMPAT_HPP__
#define __KNAPPLY__STL_COMPAT_HPP__


#include <type_traits>


#ifndef __cpp_lib_remove_cvref
namespace std {


template <class T>
struct remove_cvref {
  typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};
template <class T>
using remove_cvref_t = typename remove_cvref<T>::type;


} // namespace std
#endif


#ifdef __cpp_lib_constexpr_algorithms
#  include <algorithm>
#else
namespace std {
template <class InputIt, class T>
constexpr InputIt find(InputIt first, InputIt last, const T& value) {
  for (; first != last; ++first) {
    if (*first == value) {
      return first;
    }
  }
  return last;
}


template <class InputIt, class UnaryPredicate>
constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p) {
  for (; first != last; ++first) {
    if (p(*first)) {
      return first;
    }
  }
  return last;
}


template <class InputIt, class UnaryPredicate>
constexpr InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate q) {
  for (; first != last; ++first) {
    if (!q(*first)) {
      return first;
    }
  }
  return last;
}


template <class InputIt, class UnaryPredicate>
constexpr bool all_of(InputIt first, InputIt last, UnaryPredicate p) {
  return std::find_if_not(first, last, p) == last;
}


template <class InputIt, class UnaryPredicate>
constexpr bool any_of(InputIt first, InputIt last, UnaryPredicate p) {
  return std::find_if(first, last, p) != last;
}


template <class InputIt, class UnaryPredicate>
constexpr bool none_of(InputIt first, InputIt last, UnaryPredicate p) {
  return std::find_if(first, last, p) == last;
}


} // namespace std


#endif


#endif
