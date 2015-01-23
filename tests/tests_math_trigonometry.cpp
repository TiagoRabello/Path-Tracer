#include "math/trigonometry.hpp"

#include "catch.hpp"

SCENARIO( "It's possible to operate on angles", "[math][trigonometry]")
{
  GIVEN("two valid angles in degrees")
  {
    auto angle1 = math::degrees{ 90.0f };
    auto angle2 = math::degrees{ 180.0f };

    WHEN("adding them")
    {
      auto result = angle1 + angle2;
      THEN("the result is an angle with value equal to both values added")
      {
        REQUIRE(result.value == Approx(270.0f));
      }
    }

    WHEN("subtracting them")
    {
      auto result = angle1 - angle2;
      THEN("the result is an angle with value equal to both values subtracted")
      {
        REQUIRE(result.value == Approx(-90.0f));
      }
    }
  }
}