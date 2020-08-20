#ifndef __KNAPPLY__PORTABILITY_HPP__
#define __KNAPPLY__PORTABILITY_HPP__


namespace knapply::portability {


#if __cplusplus == 202002L
#  define KNAPPLY_CPP_IS_20 1
constexpr auto cpp = 20;
#elif __cplus_plus == 201703L
#  define KNAPPLY_CPP_IS_17 1
constexpr auto cpp  = 17;
#endif


enum class compilers {
  gcc           = 0,
  clang         = 1,
  visual_studio = 2,
};

enum class archs {
  x86_32 = 0,
  x86_64 = 1,
  arm32  = 2,
  arm64  = 3,
};


#if defined(__x86_64__) || defined(_M_AMD64)
#  define KNAPPLY_ARCH_IS_X86_64 1
constexpr auto arch = archs::x86_64;
#elif defined(__aarch64__) || defined(_M_ARM64)
#  define KNAPPLY_ARCH_IS_ARM64 1
constexpr auto arch = archs::arm64;
#else
#  define KNAPPLY_ARCH_IS_32BITS 1
#  if defined(_M_IX86) || defined(__i386__)
#    define KNAPPLY_ARCH_IS_X86_32BITS 1
constexpr auto arch = archs::x86_32;
#  elif defined(__arm__) || defined(_M_ARM)
#    define KNAPPLY_ARCH_IS_ARM_32BITS 1
constexpr auto arch = archs::arm32;
#  endif
#endif


#ifdef __GNUC__
#  define KNAPPLY_COMPILER_IS_GCC 1

#  if defined(__clang__) /* clangd intellisense workaround */
#    undef __clang__
#  endif

constexpr auto compiler = compilers::gcc;


namespace gcc {
constexpr auto major = __GNUC__;
constexpr auto minor = __GNUC_MINOR__;
} // namespace gcc
#endif


#ifdef __clang__
#  define KNAPPLY_COMPILER_IS_CLANG 1
constexpr auto compiler = compilers::clang;

namespace clang {
constexpr auto compiler_version    = __clang__;
constexpr auto compiler_minor      = __clang_minor__;
constexpr auto compiler_patchlevel = __clang_patchlevel__;
} // namespace clang
#endif


#ifdef _MSC_VER
#  define KNAPPLY_COMPILER_IS_VISUAL_STUDIO 1

constexpr auto compiler = compilers::visual_studio;

namespace visual_studio {
constexpr auto version      = _MSC_VER;
constexpr auto full_version = _MSC_FULL_VER;
} // namespace visual_studio
#endif


#ifdef KNAPPLY_COMPILER_IS_VISUAL_STUDIO

#  define really_inline __forceinline

#  ifndef likely
#    define likely(x) x
#  endif
#  ifndef unlikely
#    define unlikely(x) x
#  endif


#else

#  define really_inline inline __attribute__((always_inline))

#  ifndef likely
#    define likely(x) __builtin_expect(!!(x), 1)
#  endif
#  ifndef unlikely
#    define unlikely(x) __builtin_expect(!!(x), 0)
#  endif


#endif


} // namespace knapply::portability

#endif
