#include <math/utility.hpp>
#include <math/utility.hpp>

#include "catch.hpp"

SCENARIO( "We can create a vector from two points", "[math][utility]")
{
  GIVEN("two valid points in 3d space")
  {
    auto from = math::point3d{ 0.0f, 0.0f, 0.0f };
    auto to = math::point3d{ 1.0f, 2.0f, 3.0f };

    THEN("we can create a vector that goes from one point to the other")
    {
      auto result = math::vector3d{ 1.0f, 2.0f, 3.0f };
      REQUIRE(math::make_vector3d(from, to) == result);
    }
  }
}