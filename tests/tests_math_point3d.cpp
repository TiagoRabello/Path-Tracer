#include "math/point3d.hpp"

#include "catch.hpp"

SCENARIO( "Distance between points can be measured", "[math][point3d]")
{
  GIVEN("two valid points in 3d space")
  {
    auto p1 = math::point3d{ 0.0f, 0.0f, 0.0f };
    auto p2 = math::point3d{ 2.0f, 0.0f, 0.0f };

    THEN("we can measure their distance")
    {
      REQUIRE(math::squared_distance(p1, p2) == Approx(4.0f));
      REQUIRE(math::distance(p1, p2) == Approx(2.0f));
    }

    THEN("we can compare them")
    {
      REQUIRE(p1 != p2);
      REQUIRE(p1 == p1);
    }

    THEN("we can invert them")
    {
      auto result = math::point3d{ -2.0f, 0.0f, 0.0f };
      REQUIRE(-p2 == result);
    }
  }
}