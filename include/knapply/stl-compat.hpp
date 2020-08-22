#ifndef __KNAPPLY__STL_COMPAT_HPP__
#define __KNAPPLY__STL_COMPAT_HPP__

#include <algorithm>
#include <iterator>
#include <type_traits>

#if !defined(__cpp_lib_remove_cvref) || __cpp_lib_remove_cvref < 201711L
namespace std {

template <class T> struct remove_cvref {
  typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};
template <class T> using remove_cvref_t = typename remove_cvref<T>::type;

} // namespace std


#endif


#if !defined(__cpp_lib_ssize) || __cpp_lib_ssize < 201902L
namespace std {


template <class C>
constexpr auto ssize(const C& c)
    -> std::common_type_t<std::ptrdiff_t,
                          std::make_signed_t<decltype(c.size())>> {
  using R = std::common_type_t<std::ptrdiff_t,
                               std::make_signed_t<decltype(c.size())>>;
  return static_cast<R>(c.size());
}


} // namespace std
#endif


#ifdef __cpp_lib_constexpr_algorithms
#  define KNAPPLY_BUILTIN_CONSTEXPR_ALGOS 1
namespace knapply::portability {
constexpr auto has_builtin_constexpr_algos = true;
}
#else
#  define KNAPPLY_BUILTIN_CONSTEXPR_ALGOS 0
namespace knapply::portability {
constexpr auto has_builtin_constexpr_algos = false;
}
#endif


// #ifdef __cpp_lib_constexpr_algorithms
// #  include <algorithm>
// namespace knapply {
// constexpr auto BUILTIN_CONSTEXPR_ALGOS = true;
// }
// #else
// namespace knapply::portability {
// constexpr auto has_builtin_constexpr_algos = false;
// }


// namespace std {
// template <class InputIt, class T>
// constexpr InputIt find(InputIt first, InputIt last, const T& value) {
//   for (; first != last; ++first) {
//     if (*first == value) {
//       return first;
//     }
//   }
//   return last;
// }

// template <class InputIt, class UnaryPredicate>
// constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p) {
//   for (; first != last; ++first) {
//     if (p(*first)) {
//       return first;
//     }
//   }
//   return last;
// }


// template <class InputIt, class UnaryPredicate>
// constexpr InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate q)
// {
//   for (; first != last; ++first) {
//     if (!q(*first)) {
//       return first;
//     }
//   }
//   return last;
// }


// template <class InputIt, class ForwardIt>
// constexpr InputIt
// find_first_of(InputIt first, InputIt last, ForwardIt s_first, ForwardIt
// s_last) {
//   for (; first != last; ++first) {
//     for (ForwardIt it = s_first; it != s_last; ++it) {
//       if (*first == *it) {
//         return first;
//       }
//     }
//   }
//   return last;
// }


// template <class InputIt, class UnaryPredicate>
// constexpr bool all_of(InputIt first, InputIt last, UnaryPredicate p) {
//   return std::find_if_not(first, last, p) == last;
// }

// template <class InputIt, class UnaryPredicate>
// constexpr bool any_of(InputIt first, InputIt last, UnaryPredicate p) {
//   return std::find_if(first, last, p) != last;
// }

// template <class InputIt, class UnaryPredicate>
// constexpr bool none_of(InputIt first, InputIt last, UnaryPredicate p) {
//   return std::find_if(first, last, p) == last;
// }

// template <class InputIt, class T>
// constexpr typename iterator_traits<InputIt>::difference_type
// count(InputIt first, InputIt last, const T& value) {
//   typename iterator_traits<InputIt>::difference_type ret = 0;
//   for (; first != last; ++first) {
//     if (*first == value) {
//       ret++;
//     }
//   }
//   return ret;
// }

// } // namespace std

// #endif

#endif
