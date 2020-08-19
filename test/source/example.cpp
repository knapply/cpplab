#include "doctest/doctest.h"


void example() {
  constexpr auto test = 0;
  static_assert(test == 0);
}

TEST_CASE("example") {
  CHECK_NOTHROW(example());
}
