#ifndef __KNAPPLY__TEXT_HPP
#define __KNAPPLY__TEXT_HPP

// #include "../common.hpp"
#include <array>
#include <string_view>


namespace knapply::text {


template <typename T>
inline constexpr bool is_char(T c) {
  return !std::is_same_v<std::remove_cvref_t<T>, int> &&
         (std::is_same_v<std::remove_cvref_t<T>, char> ||
          std::is_same_v<std::remove_cvref_t<T>, wchar_t> ||
          std::is_same_v<std::remove_cvref_t<T>, char16_t> ||
          std::is_same_v<std::remove_cvref_t<T>, char32_t>);
}


constexpr std::array<char, 10> digits = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

constexpr std::array<char, 26> alpha_upper = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

constexpr std::array<char, 26> alpha_lower = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

constexpr std::array<char, 52> alpha = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', //
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

constexpr std::array<char, 62> alpha_numeric = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', //
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', //
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

constexpr std::array<char, 6> whitespace = {' ', '\f', '\n', '\r', '\t', '\v'};
// clang-format off
constexpr std::array<char, 16> punct = {
    '!', '"', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-', '.',
     '/', '~', '\''};
// clang-format on


template <typename T>
inline constexpr bool is_ascii(T c) {
  return is_char(c) && c >= 0 && c <= 127;
}
static_assert(all_are(alpha_numeric, is_ascii<char>));
static_assert(is_ascii("i"));


template <typename T>
inline constexpr bool is_digit(T c) noexcept {
  return is_char(c) && c >= 48 && c <= 57;
}
static_assert(all_are(digits, is_digit<char>));
static_assert(none_are(alpha, is_digit<char>));


template <typename T>
inline constexpr bool is_alpha_upper(T c) noexcept {
  return is_char(c) && c >= 65 && c <= 90;
}
static_assert(all_are(alpha_upper, is_alpha_upper<char>));
static_assert(none_are(alpha_lower, is_alpha_upper<char>));
static_assert(none_are(digits, is_alpha_upper<char>));


template <typename T>
inline constexpr bool is_alpha_lower(T c) noexcept {
  return is_char(c) && c >= 97 && c <= 122;
}
static_assert(all_are(alpha_upper, is_alpha_upper<char>));
static_assert(none_are(alpha_lower, is_alpha_upper<char>));
static_assert(none_are(digits, is_alpha_upper<char>));


template <typename T>
inline constexpr bool is_alpha(T c) noexcept {
  return is_char(c) && (is_alpha_upper(c) || is_alpha_lower(c));
}
static_assert(all_are(alpha, is_alpha<char>));
static_assert(none_are(digits, is_alpha<char>));


template <typename T>
inline constexpr bool is_alpha_numeric(T c) noexcept {
  return is_char(c) && (is_digit(c) || is_alpha(c));
}
static_assert(all_are(alpha_numeric, is_alpha_numeric<char>));


template <typename T>
inline constexpr bool is_punct(T c) noexcept {
  return is_char(c) && ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) ||
                        (c >= 91 && c <= 96) || (c >= 123 && c <= 126));
}
static_assert(all_are(punct, is_punct<char>));
static_assert(none_are(alpha_numeric, is_punct<char>));
static_assert(none_are(whitespace, is_punct<char>));


template <typename T>
inline constexpr bool is_space(T c) noexcept {
  return is_char(c) && ((c >= 9 && c <= 13) || c == 32);
}
static_assert(all_are(whitespace, is_space<char>));
static_assert(none_are(alpha_numeric, is_space<char>));
static_assert(none_are(punct, is_space<char>));


template <typename T, typename int_T = int>
inline constexpr int_T as_digit(T c) noexcept {
  return is_digit(c) ? c - 48 : std::numeric_limits<int_T>::min();
}
static_assert(as_digit('0') == 0);
static_assert(as_digit('1') == 1);
static_assert(as_digit('2') == 2);
static_assert(is_min(as_digit('a')));


template <typename T>
inline constexpr T to_lower(T c) noexcept {
  return is_alpha_upper(c) ? c + 32 : c;
}
static_assert(to_lower('A') == 'a');
static_assert(to_lower('Z') == 'z');


template <typename T>
inline constexpr T to_upper(T c) noexcept {
  return is_alpha_lower(c) ? c - 32 : c;
}
static_assert(to_upper('a') == 'A');
static_assert(to_upper('z') == 'Z');


inline constexpr std::string_view
substring(const std::string_view& x,
          std::size_t             pos,
          std::size_t             n = std::string_view::npos) noexcept {
  return pos <= std::size(x) ? std::string_view{std::cbegin(x) + pos,
                                                std::min(n, std::size(x) - pos)}
                             : "";
}
static_assert(substring("", 1) == "");
static_assert(substring("a", 1) == "");
static_assert(substring("abc", 0, 4) == "abc");
static_assert(substring("abc", 1) == "bc");
static_assert(substring("abc", 1, 1) == "b");


inline constexpr std::string_view lstrip(const std::string_view& s) noexcept {
  std::size_t i = 0;
  for (; i < std::size(s); ++i) {
    if (!is_space(s[i])) {
      return std::string_view(std::cbegin(s) + i);
    }
  }
  return i != std::size(s) ? s : "";
}
static_assert(lstrip("  123  ") == "123  ");
static_assert(lstrip("     ") == "");
static_assert(lstrip("     ") == "");
static_assert(lstrip(" ") == "");
static_assert(lstrip("") == "");


inline constexpr std::string_view rstrip(const std::string_view& s) noexcept {
  if (std::size(s) == 0) {
    return "";
  }
  std::size_t i = std::size(s) - 1;
  for (; i > 0; --i) {
    if (!is_space(s[i])) {
      return std::string_view(std::cbegin(s), i + 1);
    }
  }
  return i != 0 ? s : "";
}
static_assert(rstrip("  123  ") == "  123");
static_assert(rstrip("     ") == "");
static_assert(rstrip(" ") == "");
static_assert(rstrip("") == "");


inline constexpr std::string_view strip(const std::string_view& s) noexcept {
  return rstrip(lstrip(s));
}
static_assert(strip("  123  ") == "123");
static_assert(strip("     ") == "");
static_assert(strip(" ") == "");
static_assert(strip("") == "");


template <typename int_T = int>
inline constexpr int_T toi(const std::string_view& x) noexcept {
  if (x.empty()) {
    return std::numeric_limits<int_T>::min();
  }

  constexpr int_T base = 16;
  int_T           out  = 0;

  for (auto c : x) {
    if (ascii::is_digit(c)) {
      c -= '0';
    } else if (ascii::is_alpha_upper(c)) {
      c -= 'A' - 10;
    } else if (ascii::is_alpha_lower(c)) {
      c -= 'a' - 10;
    } else {
      return std::numeric_limits<int_T>::min();
    }
    out *= base;
    out += c;
  }

  return out;
}
static_assert(toi("4F") == 79);
static_assert(toi("66") == 102);
static_assert(toi("f1") == 241);
static_assert(is_min(toi("[\\")));
static_assert(is_min(toi("]^")));
static_assert(is_min(toi("_`")));
static_assert(is_min(toi("~~~")));
static_assert(is_min(toi("")));
static_assert(is_min(toi(" 4F")));
static_assert(is_min(toi(" (9 ")));

} // namespace knapply::text


#endif
