#include <catch2/catch_test_macros.hpp>

#include "orbprop/vec3.hpp"

using namespace orbprop;

TEST_CASE("Vec3 addition and scaling", "[vec3]") {
  const Vec3 a{1.0, 2.0, 3.0};
  const Vec3 b{4.0, 5.0, 6.0};
  REQUIRE(a + b == Vec3{5.0, 7.0, 9.0});
  REQUIRE(b - a == Vec3{3.0, 3.0, 3.0});
  REQUIRE(-a == Vec3{-1.0, -2.0, -3.0});
  REQUIRE(2.0 * a == a * 2.0);
  REQUIRE(a / 2.0 == Vec3{0.5, 1.0, 1.5});
}

TEST_CASE("Vec3 products", "[vec3]") {
  const Vec3 x{1.0, 0.0, 0.0};
  const Vec3 y{0.0, 1.0, 0.0};
  const Vec3 z{0.0, 0.0, 1.0};
  REQUIRE(Dot(x, y) == 0.0);
  REQUIRE(Cross(x, y) == z);
  REQUIRE(Cross(y, x) == -z);  // anticommutative
}

TEST_CASE("Vec3 norm", "[vec3]") {
  REQUIRE(Norm(Vec3{2.0, 3.0, 6.0}) == 7.0);
}

static_assert(Dot(Vec3{1.0, 2.0, 3.0}, Vec3{1.0, 2.0, 3.0}) == 14.0);