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
