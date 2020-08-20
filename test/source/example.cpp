#include "doctest/doctest.h"

#include <knapply.hpp>

void example() {
  constexpr auto test = 0;
  static_assert(test == 0);
}

TEST_CASE("example") {
  CHECK_NOTHROW(example());
}


// std::vector<std::string_view> split_csv() {
//     const std::string_view csv = "a,b,c,d,e";
//     return knapply::text::split<','>(csv);
// }

constexpr std::string_view csv = "aA,bB,cC,dD,eE, ,";


TEST_CASE("text::split") {
  CHECK_EQ(std::size(knapply::text::str_split(csv, ',')), 7);
  CHECK_EQ(knapply::text::str_split(csv, ',')[0], "aA");
  CHECK_EQ(knapply::text::str_split(csv, ',')[1], "bB");
  CHECK_EQ(knapply::text::str_split(csv, ',')[2], "cC");
  CHECK_EQ(knapply::text::str_split(csv, ',')[3], "dD");
  CHECK_EQ(knapply::text::str_split(csv, ',')[4], "eE");
  CHECK_EQ(knapply::text::str_split(csv, ',')[5], " ");
  CHECK_EQ(knapply::text::str_split(csv, ',')[6], "");
}


// TEST_CASE("text::str_count") {
//   CHECK_EQ(knapply::text::str_count<','>(csv),
//            std::count(std::cbegin(csv), std::cend(csv), ','));
// }
