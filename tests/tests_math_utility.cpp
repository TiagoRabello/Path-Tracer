#include <math/utility.hpp>
#include <math/utility.hpp>

#include "catch.hpp"

SCENARIO("We can create a vector from two points", "[math][utility]")
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

SCENARIO("We can translate a point", "[math][utility]")
{
  GIVEN("a valid point in 3d space")
  {
    auto point  = math::point3d{ 0.0f, 0.0f, 0.0f };

    GIVEN("a valid vector vector in 3d space")
    {
      auto vector = math::vector3d{ -1.0f, 2.0f, -3.0f };

      THEN("we can create a point which is the result of translating the original point")
      {
        auto result = math::point3d{ vector.x, vector.y, vector.z };
        REQUIRE(math::translated(point, vector) == result);
      }
    }

    GIVEN("a vector of length 0")
    {
      auto vector = math::vector3d{ 0.0f, 0.0f, 0.0f };

      THEN("translated point must be equal to original point")
      {
        REQUIRE(math::translated(point, vector) == point);
      }
    }
  }
}