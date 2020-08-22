#include "doctest/doctest.h"

#include <knapply.hpp>


using namespace knapply::txt;


TEST_CASE("txt::ascii::is_*") {
  SUBCASE("is_digit") {
    CHECK(knapply::all_are(ascii::digits, ascii::is_digit));
    CHECK(knapply::none_are(ascii::alpha, ascii::is_digit));
    CHECK(knapply::none_are(ascii::punct, ascii::is_digit));
    CHECK(knapply::none_are(ascii::whitespace, ascii::is_digit));
  }
  SUBCASE("is_alpha") {
    CHECK(knapply::all_are(ascii::alpha, ascii::is_alpha));
    CHECK(knapply::none_are(ascii::digits, ascii::is_alpha));
    CHECK(knapply::none_are(ascii::punct, ascii::is_alpha));
    CHECK(knapply::none_are(ascii::whitespace, ascii::is_alpha));
  }
  SUBCASE("is_upper") {
    CHECK(knapply::all_are(ascii::alpha_upper, ascii::is_upper));
    CHECK(knapply::none_are(ascii::alpha_lower, ascii::is_upper));
    CHECK(knapply::none_are(ascii::punct, ascii::is_upper));
    CHECK(knapply::none_are(ascii::whitespace, ascii::is_upper));
  }
  SUBCASE("is_lower") {
    CHECK(knapply::all_are(ascii::alpha_lower, ascii::is_lower));
    CHECK(knapply::none_are(ascii::alpha_upper, ascii::is_lower));
    CHECK(knapply::none_are(ascii::punct, ascii::is_lower));
    CHECK(knapply::none_are(ascii::whitespace, ascii::is_lower));
  }
  SUBCASE("is_alpha_numeric") {
    CHECK(knapply::all_are(ascii::alpha_numeric, ascii::is_alpha_numeric));
    CHECK(knapply::none_are(ascii::punct, ascii::is_alpha_numeric));
    CHECK(knapply::none_are(ascii::whitespace, ascii::is_alpha_numeric));
  }
  SUBCASE("is_punct") {
    CHECK(knapply::all_are(ascii::punct, ascii::is_punct));
    CHECK(knapply::none_are(ascii::alpha_lower, ascii::is_punct));
    CHECK(knapply::none_are(ascii::alpha_upper, ascii::is_punct));
    CHECK(knapply::none_are(ascii::whitespace, ascii::is_punct));
  }
  SUBCASE("is_space") {
    CHECK(knapply::all_are(ascii::whitespace, ascii::is_space));
    CHECK(knapply::none_are(ascii::alpha_lower, ascii::is_space));
    CHECK(knapply::none_are(ascii::alpha_upper, ascii::is_space));
    CHECK(knapply::none_are(ascii::punct, ascii::is_space));
  }
}


TEST_CASE("txt::sub") {
  CHECK_NOTHROW(static_assert(sub("", 1) == ""));
  CHECK_NOTHROW(static_assert(sub("a", 1) == ""));
  CHECK_NOTHROW(static_assert(sub("abc", 0, 4) == "abc"));
  CHECK_NOTHROW(static_assert(sub("abc", 1) == "bc"));
  CHECK_NOTHROW(static_assert(sub("abc", 1, 1) == "b"));
}


TEST_CASE("txt::trim_*") {
  SUBCASE("trim_left") {
    CHECK_NOTHROW(static_assert(trim_left("  123  ") == "123  "));
    CHECK_NOTHROW(static_assert(trim_left("     ") == ""));
    CHECK_NOTHROW(static_assert(trim_left(" ") == ""));
    CHECK_NOTHROW(static_assert(trim_left("") == ""));
  }
  SUBCASE("timr_right") {
    CHECK_NOTHROW(static_assert(trim_right("  123  ") == "  123"));
    CHECK_NOTHROW(static_assert(trim_right("     ") == ""));
    CHECK_NOTHROW(static_assert(trim_right(" ") == ""));
    CHECK_NOTHROW(static_assert(trim_right("") == ""));
  }
  SUBCASE("trim") {
    CHECK_NOTHROW(static_assert(trim("  123  ") == "123"));
    CHECK_NOTHROW(static_assert(trim("     ") == ""));
    CHECK_NOTHROW(static_assert(trim(" ") == ""));
    CHECK_NOTHROW(static_assert(trim("") == ""));
  }
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
  CHECK_EQ(count("", ','), 0);
  CHECK_EQ(count(" , , ", ','), 2);
  CHECK_EQ(count(" 11 , 11 "sv, '1'), 4);
  CHECK_EQ(count(" 11 , 11 "sv, "1"sv), 4);
  CHECK_EQ(count(" 11 , 11 "sv, "11"sv), 2);
  CHECK_EQ(count("11 , 11 "sv, " , 11"sv), 1);
}


TEST_CASE("txt::split*") {
  SUBCASE("split") {
    constexpr std::string_view csv = ",aA,bB,c,d , e ,, ,1";

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
  SUBCASE("split_fixed") {
    constexpr std::string_view csv = ",aA,bB,c,d , e ,, ,1";

    auto str_split_fixed = split_fixed<9>(csv, ',');
    CHECK_EQ(str_split_fixed[0], "");
    CHECK_EQ(str_split_fixed[1], "aA");
    CHECK_EQ(str_split_fixed[2], "bB");
    CHECK_EQ(str_split_fixed[3], "c");
    CHECK_EQ(str_split_fixed[4], "d ");
    CHECK_EQ(str_split_fixed[5], " e ");
    CHECK_EQ(str_split_fixed[6], "");
    CHECK_EQ(str_split_fixed[7], " ");
    CHECK_EQ(str_split_fixed[8], "1");

    auto str_split_fixed2 = split_fixed<8>(csv, ',');
    CHECK_EQ(str_split_fixed2[0], "");
    CHECK_EQ(str_split_fixed2[1], "aA");
    CHECK_EQ(str_split_fixed2[2], "bB");
    CHECK_EQ(str_split_fixed2[3], "c");
    CHECK_EQ(str_split_fixed2[4], "d ");
    CHECK_EQ(str_split_fixed2[5], " e ");
    CHECK_EQ(str_split_fixed2[6], "");
    CHECK_EQ(str_split_fixed2[7], " ");

    constexpr std::string_view str_split_arabic = "أَلْحُرُوف ٱلْعَرَبِيَّة";
    CHECK_EQ(split_fixed<2>(str_split_arabic, ' ')[1], "ٱلْعَرَبِيَّة");

    constexpr std::string_view str_split_arabic2 = "أَلْحُرُوف   ٱلْعَرَبِيَّة";
    CHECK_EQ(split_fixed<2>(str_split_arabic2, "   "sv)[1], "ٱلْعَرَبِيَّة");
  }
}
