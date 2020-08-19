#include "doctest/doctest.h"
#include "knapply/portability.hpp"


#include <knapply.hpp>


void example() {
  constexpr auto test = 0;
  static_assert(test == 0);
}

TEST_CASE("example") {
  CHECK_NOTHROW(example());
}
