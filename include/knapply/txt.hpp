#ifndef __KNAPPLY__TEXT_HPP
#define __KNAPPLY__TEXT_HPP


#include "common.hpp"


namespace knapply::txt {


using namespace std::literals::string_view_literals;


namespace ascii {
constexpr std::array<char, 10> digits = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

constexpr std::array<char, 26> alpha_upper = { //
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

constexpr std::array<char, 26> alpha_lower = { //
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

constexpr std::array<char, 16> punct = {
    '!', '"', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/', '~', '\''};
} // namespace ascii


template <class char_T>
constexpr bool is_ascii(const char_T c) noexcept {
  if constexpr (is_char_ish_v<char_T>) {
    if constexpr (std::is_unsigned_v<char_T>) {
      return c <= 127;
    } else {
      return c <= 127 && c >= 0;
    }
  } else {
    return false;
  }
}
static_assert(std::all_of(std::cbegin(ascii::alpha_numeric),
                          std::cend(ascii::alpha_numeric),
                          is_ascii<char>));
static_assert(is_ascii(static_cast<unsigned char>(1)));
static_assert(!is_ascii(static_cast<char>(-1)));
static_assert(!is_ascii(1));
static_assert(!is_ascii(static_cast<int8_t>(1)));
static_assert(!is_ascii(static_cast<uint16_t>(1)));
static_assert(!is_ascii(static_cast<uint32_t>(1)));
static_assert(!is_ascii(static_cast<uint64_t>(1)));
static_assert(!is_ascii("رَ"sv));


namespace ascii {


constexpr bool is_digit(const char c) noexcept {
  return c >= 48 && c <= 57;
}
static_assert(std::all_of(std::cbegin(digits), std::cend(digits), is_digit));
static_assert(std::none_of(std::cbegin(alpha), std::cend(alpha), is_digit));


constexpr bool is_upper(const char c) noexcept {
  return c >= 65 && c <= 90;
}
static_assert(std::all_of(std::cbegin(alpha_upper), std::cend(alpha_upper), is_upper));
static_assert(std::none_of(std::cbegin(alpha_lower), std::cend(alpha_lower), is_upper));
static_assert(std::none_of(std::cbegin(digits), std::cend(digits), is_upper));


constexpr bool is_lower(const char c) noexcept {
  return c >= 97 && c <= 122;
}
static_assert(std::all_of(std::cbegin(alpha_lower), std::cend(alpha_lower), is_lower));
static_assert(std::none_of(std::cbegin(alpha_upper), std::cend(alpha_upper), is_lower));
static_assert(std::none_of(std::cbegin(digits), std::cend(digits), is_lower));


constexpr bool is_alpha(const char c) noexcept {
  return (is_upper(c) || is_lower(c));
}
static_assert(std::all_of(std::cbegin(alpha), std::cend(alpha), is_alpha));
static_assert(std::none_of(std::cbegin(digits), std::cend(digits), is_alpha));


constexpr bool is_alpha_numeric(const char c) noexcept {
  return (is_digit(c) || is_alpha(c));
}
static_assert(std::all_of(std::cbegin(alpha_numeric),
                          std::cend(alpha_numeric),
                          is_alpha_numeric));


constexpr bool is_punct(const char c) noexcept {
  return ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) ||
          (c >= 123 && c <= 126));
}
static_assert(std::all_of(std::cbegin(punct), std::cend(punct), is_punct));
static_assert(std::none_of(std::cbegin(alpha_numeric),
                           std::cend(alpha_numeric),
                           is_punct));
static_assert(std::none_of(std::cbegin(whitespace), std::cend(whitespace), is_punct));


constexpr bool is_space(const char c) noexcept {
  return ((c >= 9 && c <= 13) || c == 32);
}
static_assert(std::all_of(std::cbegin(whitespace), std::cend(whitespace), is_space));
static_assert(std::none_of(std::cbegin(alpha_numeric),
                           std::cend(alpha_numeric),
                           is_space));
static_assert(std::none_of(std::cbegin(punct), std::cend(punct), is_space));


template <typename int_T = int>
constexpr int_T as_digit(const char c) noexcept {
  return is_digit(c) ? c - 48 : std::numeric_limits<int_T>::min();
}
static_assert(as_digit('0') == 0);
static_assert(as_digit('1') == 1);
static_assert(as_digit('2') == 2);
static_assert(is_min(as_digit('a')));


constexpr char to_lower(const char c) noexcept {
  return is_upper(c) ? c + 32 : c;
}
static_assert(to_lower('A') == 'a');
static_assert(to_lower('Z') == 'z');


constexpr char to_upper(const char c) noexcept {
  return is_lower(c) ? c - 32 : c;
}
static_assert(to_upper('a') == 'A');
static_assert(to_upper('z') == 'Z');


} // namespace ascii


constexpr std::string_view sub(const std::string_view s,
                               std::size_t            pos,
                               std::size_t n = std::string_view::npos) noexcept {
  return pos <= std::size(s)
             ? std::string_view{std::cbegin(s) + pos, std::min(n, std::size(s) - pos)}
             : "";
}
static_assert(sub("", 1) == "");
static_assert(sub("a", 1) == "");
static_assert(sub("abc", 0, 4) == "abc");
static_assert(sub("abc", 1) == "bc");
static_assert(sub("abc", 1, 1) == "b");


constexpr std::string_view trim_left(const std::string_view s) noexcept {
  std::size_t i = 0;
  for (; i < std::size(s); ++i) {
    if (!ascii::is_space(s[i])) {
      return std::string_view(std::cbegin(s) + i);
    }
  }
  return i != std::size(s) ? s : "";
}
static_assert(trim_left("  123  ") == "123  ");
static_assert(trim_left("     ") == "");
static_assert(trim_left(" ") == "");
static_assert(trim_left("") == "");


constexpr std::string_view trim_right(const std::string_view s) noexcept {
  if (std::size(s) == 0) {
    return "";
  }
  std::size_t i = std::size(s) - 1;
  for (; i > 0; --i) {
    if (!ascii::is_space(s[i])) {
      return std::string_view(std::cbegin(s), i + 1);
    }
  }
  return i != 0 ? s : "";
}
static_assert(trim_right("  123  ") == "  123");
static_assert(trim_right("     ") == "");
static_assert(trim_right(" ") == "");
static_assert(trim_right("") == "");


constexpr std::string_view trim(const std::string_view s) noexcept {
  return trim_right(trim_left(s));
}
static_assert(trim("  123  ") == "123");
static_assert(trim("     ") == "");
static_assert(trim(" ") == "");
static_assert(trim("") == "");


template <typename int_T = int>
constexpr int_T toi(const std::string_view s) noexcept {
  if (s.empty()) {
    return std::numeric_limits<int_T>::min();
  }

  constexpr int_T base = 16;
  int_T           out  = 0;
  for (auto c : s) {
    if (ascii::is_digit(c)) {
      c -= '0';
    } else if (ascii::is_upper(c)) {
      c -= 'A' - 10;
    } else if (ascii::is_lower(c)) {
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
static_assert(toi("[\\") == std::numeric_limits<int>::min());
static_assert(toi("]^") == std::numeric_limits<int>::min());
static_assert(toi("_`") == std::numeric_limits<int>::min());
static_assert(toi("~~~") == std::numeric_limits<int>::min());
static_assert(toi("") == std::numeric_limits<int>::min());
static_assert(toi(" 4F") == std::numeric_limits<int>::min());
static_assert(toi(" (9 ") == std::numeric_limits<int>::min());


template <typename needle_T>
constexpr std::size_t count(const std::string_view s, const needle_T needle) noexcept {
  std::size_t out = 0;

  if constexpr (is_same_ish_v<needle_T, std::string_view>) {
    for (auto loc = s.find(needle); loc < std::size(s); loc = s.find(needle, loc + 1)) {
      out++;
    }
  } else {
    for (auto loc = std::find(std::cbegin(s), std::cend(s), needle); loc != std::cend(s);
         loc      = std::find(loc + 1, std::cend(s), needle)) {
      out++;
    }
  }
  return out;
}
static_assert(count("", ',') == 0);
static_assert(count(" , , ", ',') == 2);
static_assert(count(" 11 , 11 "sv, '1') == 4);
static_assert(count(" 11 , 11 ", "1"sv) == 4);
static_assert(count(" 11 , 11 ", "11"sv) == 2);
static_assert(count("11 , 11 ", " , 11"sv) == 1);


template <typename delim_T>
std::vector<std::string_view> split(const std::string_view s,
                                    const delim_T          delim) noexcept {
  std::vector<std::string_view> out;
  std::size_t                   left = 0;
  for (auto right = s.find(delim); right < std::size(s); right = s.find(delim, left)) {
    out.emplace_back(std::cbegin(s) + left, right - left);
    left = right + 1;
  }
  out.emplace_back(std::cbegin(s) + left);
  return out;
}


template <std::size_t n, typename needle_T>
constexpr std::array<std::string_view, n> split_fixed(const std::string_view s,
                                                      const needle_T delim) noexcept {
  std::array<std::string_view, n> out;

  auto        it   = std::begin(out);
  std::size_t left = 0;

  if constexpr (is_same_ish_v<needle_T, std::string_view>) {
    for (auto right = s.find(delim); right < std::size(s) && it != std::cend(out);) {
      *it++ = std::string_view(std::cbegin(s) + left, right - left);
      left  = right + std::size(delim);
      right = s.find(delim, left);
    }
  } else {
    for (auto right = std::find(std::cbegin(s), std::cend(s), delim);
         right != std::cend(s) && it != std::cend(out);) {
      *it++ = std::string_view(
          std::cbegin(s) + left,
          static_cast<std::size_t>(std::distance(std::cbegin(s), right)) - left);
      left  = static_cast<std::size_t>(std::distance(std::cbegin(s), right)) + 1;
      right = std::find(std::cbegin(s) + left, std::cend(s), delim);
    }
  }

  if (it != std::cend(out)) {
    *it = std::string_view(std::data(s) + left);
  }

  return out;
}
namespace test_vals {
constexpr auto csv    = ",aA,bB,c,d , e ,, ,1";
constexpr auto fixed  = split_fixed<9>(csv, ',');
constexpr auto fixed2 = split_fixed<8>(csv, ',');
constexpr auto arabic = "أَلْحُرُوف   ٱلْعَرَبِيَّة";
} // namespace test_vals
static_assert(test_vals::fixed[0] == "");
static_assert(test_vals::fixed[1] == "aA");
static_assert(test_vals::fixed[2] == "bB");
static_assert(test_vals::fixed[3] == "c");
static_assert(test_vals::fixed[4] == "d ");
static_assert(test_vals::fixed[5] == " e ");
static_assert(test_vals::fixed[6] == "");
static_assert(test_vals::fixed[7] == " ");
static_assert(test_vals::fixed[8] == "1");
static_assert(test_vals::fixed2[0] == "");
static_assert(test_vals::fixed2[1] == "aA");
static_assert(test_vals::fixed2[2] == "bB");
static_assert(test_vals::fixed2[3] == "c");
static_assert(test_vals::fixed2[4] == "d ");
static_assert(test_vals::fixed2[5] == " e ");
static_assert(test_vals::fixed2[6] == "");
static_assert(test_vals::fixed2[7] == " ");
static_assert(split_fixed<2>(test_vals::csv, " , "sv)[0] == ",aA,bB,c,d");
static_assert(split_fixed<2>(test_vals::csv, " , "sv)[1] == "e ,, ,1");
static_assert(split_fixed<2>(test_vals::arabic, "   "sv)[1] == "ٱلْعَرَبِيَّة");


} // namespace knapply::txt


#endif
