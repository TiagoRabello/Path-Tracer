#include "math/vector3d.hpp"

#include "catch.hpp"

SCENARIO( "We can operate on vectors", "[math][vector3d]")
{
  GIVEN("a valid vector in 3d space")
  {
    auto x = math::vector3d{ 2.0f, 0.0f, 0.0f };

    GIVEN("another valid vector in 3d space")
    {
      auto y = math::vector3d{ 0.0f, 1.0f, 0.0f };

      THEN("we can add them")
      {
        auto expected = math::vector3d{ 2.0f, 1.0f, 0.0f };
        REQUIRE((x + y) == expected);
      }

      THEN("we can subtract them")
      {
        auto expected = math::vector3d{ 2.0f, -1.0f, 0.0f };
        REQUIRE((x - y) == expected);
      }

      THEN("we can calculate their dot product")
      {
        REQUIRE(math::dot(x, y) == 0.0f);
      }

      THEN("we can calculate their cross product")
      {
        auto expected = math::vector3d{ 0.0f, 0.0f, 2.0f };
        REQUIRE(math::cross(x, y) == expected);
      }

      THEN("we can compare them")
      {
        REQUIRE(x != y);
        REQUIRE(x == x);
      }
    }

    THEN("we can scale it")
    {
      auto result = math::vector3d{ 1.0f, 0.0f, 0.0f };
      REQUIRE(math::scaled(x, 0.5f) == result);
    }

    THEN("we can invert it")
    {
      auto result = math::vector3d{ -2.0f, 0.0f, 0.0f };
      REQUIRE(-x == result);
    }

    THEN("we can measure it's length")
    {
      REQUIRE(math::squared_length(x) == 4.0f);
      REQUIRE(math::length(x) == 2.0f);
    }

    THEN("we can normalize it")
    {
      REQUIRE(math::squared_length(math::normalized(x)) == 1.0f);
      REQUIRE(math::length(math::normalized(x)) == 1.0f);
    }
  }
}