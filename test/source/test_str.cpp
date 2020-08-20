#include "doctest/doctest.h"

#include <knapply.hpp>


TEST_CASE("str::is_digit") {
  CHECK_NOTHROW(static_assert(std::all_of(std::cbegin(knapply::str::digits),
                                          std::cend(knapply::str::digits),
                                          knapply::str::is_digit)));
  CHECK_NOTHROW(static_assert(std::none_of(std::cbegin(knapply::str::alpha),
                                           std::cend(knapply::str::alpha),
                                           knapply::str::is_digit)));
}


TEST_CASE("str::is_upper / str::is_upper") {
  using namespace knapply::str;

  CHECK_NOTHROW(static_assert(
      std::all_of(std::cbegin(alpha_upper), std::cend(alpha_upper), is_upper)));
  CHECK_NOTHROW(static_assert(
      std::none_of(std::cbegin(alpha_lower), std::cend(alpha_lower), is_upper)));
  CHECK_NOTHROW(
      static_assert(std::none_of(std::cbegin(digits), std::cend(digits), is_upper)));
  CHECK_NOTHROW(
      static_assert(std::none_of(std::cbegin(punct), std::cend(punct), is_upper)));

  CHECK_NOTHROW(static_assert(
      std::all_of(std::cbegin(alpha_lower), std::cend(alpha_lower), is_lower)));
  CHECK_NOTHROW(static_assert(
      std::none_of(std::cbegin(alpha_upper), std::cend(alpha_upper), is_lower)));
  CHECK_NOTHROW(
      static_assert(std::none_of(std::cbegin(digits), std::cend(digits), is_lower)));
  CHECK_NOTHROW(
      static_assert(std::none_of(std::cbegin(punct), std::cend(punct), is_lower)));
}


TEST_CASE("str::is_punct / str::is_space") {
  using namespace knapply::str;

  CHECK_NOTHROW(
      static_assert(std::all_of(std::cbegin(punct), std::cend(punct), is_punct)));
  CHECK_NOTHROW(static_assert(
      std::none_of(std::cbegin(alpha_numeric), std::cend(alpha_numeric), is_punct)));
  CHECK_NOTHROW(static_assert(
      std::none_of(std::cbegin(whitespace), std::cend(whitespace), is_punct)));

  CHECK_NOTHROW(static_assert(
      std::all_of(std::cbegin(whitespace), std::cend(whitespace), is_space)));
  CHECK_NOTHROW(static_assert(
      std::none_of(std::cbegin(alpha_numeric), std::cend(alpha_numeric), is_space)));
  CHECK_NOTHROW(
      static_assert(std::none_of(std::cbegin(punct), std::cend(punct), is_space)));
}


TEST_CASE("str::to_lower / str::to_upper") {
  using namespace knapply::str;

  CHECK_NOTHROW(static_assert(to_lower('A') == 'a'));
  CHECK_NOTHROW(static_assert(to_lower('Z') == 'z'));

  CHECK_NOTHROW(static_assert(to_upper('a') == 'A'));
  CHECK_NOTHROW(static_assert(to_upper('z') == 'Z'));
}


TEST_CASE("str::sub") {
  using namespace knapply::str;

  CHECK_NOTHROW(static_assert(sub("", 1) == ""));
  CHECK_NOTHROW(static_assert(sub("a", 1) == ""));
  CHECK_NOTHROW(static_assert(sub("abc", 0, 4) == "abc"));
  CHECK_NOTHROW(static_assert(sub("abc", 1) == "bc"));
  CHECK_NOTHROW(static_assert(sub("abc", 1, 1) == "b"));
}


TEST_CASE("str::trim_left / str::trim_right / str::trim") {
  using namespace knapply::str;

  CHECK_NOTHROW(static_assert(trim_left("  123  ") == "123  "));
  CHECK_NOTHROW(static_assert(trim_left("     ") == ""));
  CHECK_NOTHROW(static_assert(trim_left(" ") == ""));
  CHECK_NOTHROW(static_assert(trim_left("") == ""));

  CHECK_NOTHROW(static_assert(trim_right("  123  ") == "  123"));
  CHECK_NOTHROW(static_assert(trim_right("     ") == ""));
  CHECK_NOTHROW(static_assert(trim_right(" ") == ""));
  CHECK_NOTHROW(static_assert(trim_right("") == ""));

  CHECK_NOTHROW(static_assert(trim("  123  ") == "123"));
  CHECK_NOTHROW(static_assert(trim("     ") == ""));
  CHECK_NOTHROW(static_assert(trim(" ") == ""));
  CHECK_NOTHROW(static_assert(trim("") == ""));
}


TEST_CASE("str::toi") {
  using namespace knapply::str;

  CHECK_NOTHROW(static_assert(toi("4F") == 79));
  CHECK_NOTHROW(static_assert(toi("66") == 102));
  CHECK_NOTHROW(static_assert(toi("f1") == 241));
  CHECK_NOTHROW(static_assert(toi("[\\") == std::numeric_limits<int>::min()));
  CHECK_NOTHROW(static_assert(toi("]^") == std::numeric_limits<int>::min()));
  CHECK_NOTHROW(static_assert(toi("_`") == std::numeric_limits<int>::min()));
  CHECK_NOTHROW(static_assert(toi("~~~") == std::numeric_limits<int>::min()));
  CHECK_NOTHROW(static_assert(toi("") == std::numeric_limits<int>::min()));
  CHECK_NOTHROW(static_assert(toi(" 4F") == std::numeric_limits<int>::min()));
  CHECK_NOTHROW(static_assert(toi(" (9 ") == std::numeric_limits<int>::min()));
}


TEST_CASE("str::count") {
  using namespace knapply::str;

  CHECK_NOTHROW(static_assert(count("", ',') == 0));
  CHECK_NOTHROW(static_assert(count(" , , ", ',') == 2));
  CHECK_NOTHROW(static_assert(count(" 11 , 11 ", '1') == 4));
  CHECK_NOTHROW(static_assert(count(" 11 , 11 ", "1") == 4));
  CHECK_NOTHROW(static_assert(count(" 11 , 11 ", "11") == 2));
  CHECK_NOTHROW(static_assert(count("11 , 11 ", " , 11") == 1));
}


TEST_CASE("str::split") {
  constexpr auto csv = ",aA,bB,c,d , e ,, ,1";

  const auto str_split = knapply::str::split(csv, ',');
  CHECK_EQ(std::size(str_split), 9);
  CHECK_EQ(str_split[0], "");
  CHECK_EQ(str_split[1], "aA");
  CHECK_EQ(str_split[2], "bB");
  CHECK_EQ(str_split[3], "c");
  CHECK_EQ(str_split[4], "d ");
  CHECK_EQ(str_split[5], " e ");
  CHECK_EQ(str_split[6], "");
  CHECK_EQ(str_split[7], " ");
  CHECK_EQ(str_split[8], "1");
}

TEST_CASE("str::split") {
  constexpr auto csv = ",aA,bB,c,d , e ,, ,1";

  constexpr auto str_split_fixed = knapply::str::split_fixed<9>(csv, ',');
  CHECK_NOTHROW(static_assert(str_split_fixed[0] == ""));
  CHECK_NOTHROW(static_assert(str_split_fixed[1] == "aA"));
  CHECK_NOTHROW(static_assert(str_split_fixed[2] == "bB"));
  CHECK_NOTHROW(static_assert(str_split_fixed[3] == "c"));
  CHECK_NOTHROW(static_assert(str_split_fixed[4] == "d "));
  CHECK_NOTHROW(static_assert(str_split_fixed[5] == " e "));
  CHECK_NOTHROW(static_assert(str_split_fixed[6] == ""));
  CHECK_NOTHROW(static_assert(str_split_fixed[7] == " "));
  CHECK_NOTHROW(static_assert(str_split_fixed[8] == "1"));

  constexpr auto str_split_fixed2 = knapply::str::split_fixed<8>(csv, ',');
  CHECK_NOTHROW(static_assert(str_split_fixed2[0] == ""));
  CHECK_NOTHROW(static_assert(str_split_fixed2[1] == "aA"));
  CHECK_NOTHROW(static_assert(str_split_fixed2[2] == "bB"));
  CHECK_NOTHROW(static_assert(str_split_fixed2[3] == "c"));
  CHECK_NOTHROW(static_assert(str_split_fixed2[4] == "d "));
  CHECK_NOTHROW(static_assert(str_split_fixed2[5] == " e "));
  CHECK_NOTHROW(static_assert(str_split_fixed2[6] == ""));
  CHECK_NOTHROW(static_assert(str_split_fixed2[7] == " "));

  constexpr auto str_split_arabic = "أَلْحُرُوف ٱلْعَرَبِيَّة";
  CHECK_NOTHROW(
      static_assert(knapply::str::split_fixed<2>(str_split_arabic, ' ')[1] == "ٱلْعَرَبِيَّة"));
}
