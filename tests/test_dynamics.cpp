#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "orbprop/constants.hpp"
#include "orbprop/dynamics.hpp"

using namespace orbprop;
using Catch::Matchers::WithinRel;

TEST_CASE("Circular velocity at 400 km altitude", "[dynamics]") {
    const double r = kREarth + 400.0;
    const double v = CircularVelocity(r, kMuEarth);
    REQUIRE_THAT(v, WithinRel(7.668558, 1e-6));
};

using Catch::Matchers::WithinAbs;
TEST_CASE("Two-body acceleration magnitude at 400 km altitude", "[dynamics]") {
  const Vec3 r{kREarth + 400.0, 0.0, 0.0};
  const Vec3 a = TwoBodyAcceleration(r, kMuEarth);
  // mu / r^2 = 398600.4418 / 6778.137^2, computed independently in Python.
  REQUIRE_THAT(Norm(a), WithinRel(0.008675951000931728, 1e-12));
}

TEST_CASE("Two-body acceleration points at the centre", "[dynamics]") {
  const Vec3 r{4000.0, -5000.0, 3000.0};
  const Vec3 a = TwoBodyAcceleration(r, kMuEarth);
  // cos(angle between a and r) must be -1: anti-parallel.
  const double cos_angle = Dot(a, r) / (Norm(a) * Norm(r));
  REQUIRE_THAT(cos_angle, WithinAbs(-1.0, 1e-15));
}

TEST_CASE("Two-body acceleration follows the inverse-square law", "[dynamics]") {
  const Vec3 r1{7000.0, 0.0, 0.0};
  const Vec3 r2 = 2.0 * r1;
  const double ratio = Norm(TwoBodyAcceleration(r1, kMuEarth)) /
                       Norm(TwoBodyAcceleration(r2, kMuEarth));
  REQUIRE_THAT(ratio, WithinRel(4.0, 1e-14));
}

TEST_CASE("Circular speed matches centripetal acceleration", "[dynamics]") {
  const double r = kREarth + 400.0;
  const double v = CircularVelocity(r, kMuEarth);
  const double a = Norm(TwoBodyAcceleration(Vec3{r, 0.0, 0.0}, kMuEarth));
  REQUIRE_THAT(a, WithinRel(v * v / r, 1e-14));  // a_c = v^2 / r
}