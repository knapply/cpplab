#include "doctest/doctest.h"

#include <knapply.hpp>


using namespace knapply::txt;


TEST_CASE("txt::ascii::is_digit") {
  CHECK_NOTHROW(static_assert(std::all_of(
      std::cbegin(ascii::digits), std::cend(ascii::digits), ascii::is_digit)));
  CHECK_NOTHROW(static_assert(
      std::none_of(std::cbegin(ascii::alpha), std::cend(ascii::alpha), ascii::is_digit)));
}

TEST_CASE("txt::ascii::is_upper / txt::ascii::is_upper") {

  CHECK_NOTHROW(static_assert(std::all_of(
      std::cbegin(ascii::alpha_upper), std::cend(ascii::alpha_upper), ascii::is_upper)));
  CHECK_NOTHROW(static_assert(std::none_of(
      std::cbegin(ascii::alpha_lower), std::cend(ascii::alpha_lower), ascii::is_upper)));
  CHECK_NOTHROW(static_assert(std::none_of(
      std::cbegin(ascii::digits), std::cend(ascii::digits), ascii::is_upper)));
  CHECK_NOTHROW(static_assert(
      std::none_of(std::cbegin(ascii::punct), std::cend(ascii::punct), ascii::is_upper)));

  CHECK_NOTHROW(static_assert(std::all_of(
      std::cbegin(ascii::alpha_lower), std::cend(ascii::alpha_lower), ascii::is_lower)));
  CHECK_NOTHROW(static_assert(std::none_of(
      std::cbegin(ascii::alpha_upper), std::cend(ascii::alpha_upper), ascii::is_lower)));
  CHECK_NOTHROW(static_assert(std::none_of(
      std::cbegin(ascii::digits), std::cend(ascii::digits), ascii::is_lower)));
  CHECK_NOTHROW(static_assert(
      std::none_of(std::cbegin(ascii::punct), std::cend(ascii::punct), ascii::is_lower)));
}

TEST_CASE("txt::is_punct / txt::is_space") {
  CHECK_NOTHROW(static_assert(
      std::all_of(std::cbegin(ascii::punct), std::cend(ascii::punct), ascii::is_punct)));
  CHECK_NOTHROW(static_assert(std::none_of(std::cbegin(ascii::alpha_numeric),
                                           std::cend(ascii::alpha_numeric),
                                           ascii::is_punct)));
  CHECK_NOTHROW(static_assert(std::none_of(
      std::cbegin(ascii::whitespace), std::cend(ascii::whitespace), ascii::is_punct)));

  CHECK_NOTHROW(static_assert(std::all_of(
      std::cbegin(ascii::whitespace), std::cend(ascii::whitespace), ascii::is_space)));
  CHECK_NOTHROW(static_assert(std::none_of(std::cbegin(ascii::alpha_numeric),
                                           std::cend(ascii::alpha_numeric),
                                           ascii::is_space)));
  CHECK_NOTHROW(static_assert(
      std::none_of(std::cbegin(ascii::punct), std::cend(ascii::punct), ascii::is_space)));
}

TEST_CASE("txt::ascii::to_lower / txt::ascii::to_upper") {

  CHECK_NOTHROW(static_assert(ascii::to_lower('A') == 'a'));
  CHECK_NOTHROW(static_assert(ascii::to_lower('Z') == 'z'));

  CHECK_NOTHROW(static_assert(ascii::to_upper('a') == 'A'));
  CHECK_NOTHROW(static_assert(ascii::to_upper('z') == 'Z'));
}

TEST_CASE("txt::sub") {
  CHECK_NOTHROW(static_assert(sub("", 1) == ""));
  CHECK_NOTHROW(static_assert(sub("a", 1) == ""));
  CHECK_NOTHROW(static_assert(sub("abc", 0, 4) == "abc"));
  CHECK_NOTHROW(static_assert(sub("abc", 1) == "bc"));
  CHECK_NOTHROW(static_assert(sub("abc", 1, 1) == "b"));
}


TEST_CASE("txt::trim_left / txt::trim_right / txt::trim") {
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


TEST_CASE("txt::toi") {
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


TEST_CASE("txt::count") {
  CHECK_NOTHROW(static_assert(count("", ',') == 0));
  CHECK_NOTHROW(static_assert(count(" , , ", ',') == 2));
  CHECK_NOTHROW(static_assert(count(" 11 , 11 "sv, '1') == 4));
  CHECK_NOTHROW(static_assert(count(" 11 , 11 "sv, "1"sv) == 4));
  CHECK_NOTHROW(static_assert(count(" 11 , 11 "sv, "11"sv) == 2));
  CHECK_NOTHROW(static_assert(count("11 , 11 "sv, " , 11"sv) == 1));
}


TEST_CASE("txt::split") {
  constexpr auto csv = ",aA,bB,c,d , e ,, ,1";

  const auto str_split = knapply::txt::split(csv, ',');
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


TEST_CASE("txt::split_fixed") {
  constexpr auto csv = ",aA,bB,c,d , e ,, ,1";

  constexpr auto str_split_fixed = split_fixed<9>(csv, ',');
  CHECK_NOTHROW(static_assert(str_split_fixed[0] == ""));
  CHECK_NOTHROW(static_assert(str_split_fixed[1] == "aA"));
  CHECK_NOTHROW(static_assert(str_split_fixed[2] == "bB"));
  CHECK_NOTHROW(static_assert(str_split_fixed[3] == "c"));
  CHECK_NOTHROW(static_assert(str_split_fixed[4] == "d "));
  CHECK_NOTHROW(static_assert(str_split_fixed[5] == " e "));
  CHECK_NOTHROW(static_assert(str_split_fixed[6] == ""));
  CHECK_NOTHROW(static_assert(str_split_fixed[7] == " "));
  CHECK_NOTHROW(static_assert(str_split_fixed[8] == "1"));

  constexpr auto str_split_fixed2 = split_fixed<8>(csv, ',');
  CHECK_NOTHROW(static_assert(str_split_fixed2[0] == ""));
  CHECK_NOTHROW(static_assert(str_split_fixed2[1] == "aA"));
  CHECK_NOTHROW(static_assert(str_split_fixed2[2] == "bB"));
  CHECK_NOTHROW(static_assert(str_split_fixed2[3] == "c"));
  CHECK_NOTHROW(static_assert(str_split_fixed2[4] == "d "));
  CHECK_NOTHROW(static_assert(str_split_fixed2[5] == " e "));
  CHECK_NOTHROW(static_assert(str_split_fixed2[6] == ""));
  CHECK_NOTHROW(static_assert(str_split_fixed2[7] == " "));

  constexpr auto str_split_arabic = "أَلْحُرُوف ٱلْعَرَبِيَّة";
  CHECK_NOTHROW(static_assert(split_fixed<2>(str_split_arabic, ' ')[1] == "ٱلْعَرَبِيَّة"));

  constexpr auto str_split_arabic2 = "أَلْحُرُوف   ٱلْعَرَبِيَّة";
  CHECK_NOTHROW(
      static_assert(split_fixed<2>(str_split_arabic2, "   "sv)[1] == "ٱلْعَرَبِيَّة"));
}
