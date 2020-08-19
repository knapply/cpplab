#ifndef __KNAPPLY__STL_COMPAT_HPP__
#define __KNAPPLY__STL_COMPAT_HPP__

#include <type_traits>

namespace std {

#ifndef __cpp_lib_remove_cvref
template <class T>
struct remove_cvref {
  typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};
template <class T>
using remove_cvref_t = typename remove_cvref<T>::type;

#endif

} // namespace std


#endif
