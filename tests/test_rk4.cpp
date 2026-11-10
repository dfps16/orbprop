#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <cmath>
#include <numbers>

#include "orbprop/constants.hpp"
#include "orbprop/dynamics.hpp"
#include "orbprop/rk4.hpp"

using namespace orbprop;
using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

TEST_CASE("RK4 circular orbit returns to start after one period", "[rk4]") {
  const double r0 = kREarth + 400.0;
  const State y0{{r0, 0, 0}, {0.0, CircularVelocity(r0, kMuEarth), 0.0}};
  const double period =
      2.0 * std::numbers::pi * std::sqrt(r0 * r0 * r0 / kMuEarth);

  const int n_steps = 1000;
  const double h = period / n_steps;
  const auto two_body = [](double /*t*/, const State& y) {
    return TwoBodyDerivative(y, kMuEarth);
  };

  const State y1 = PropagateRk4(y0, 0.0, h, n_steps, two_body);

  REQUIRE_THAT(Norm(y1.r - y0.r), WithinAbs(0.0, 1e-5));
}

namespace {

constexpr double kDegToRad = std::numbers::pi / 180.0;

// Elliptical, inclined test orbit: a = 8000 km, e = 0.1, i = 51.6 deg,
// starting at perigee.
constexpr double kA = 8000.0;
constexpr double kE = 0.1;

State PerigeeState() {
  const double r_p = kA * (1.0 - kE);
  // Vis-viva at perigee: v^2 = mu (2/r - 1/a) = mu (1 + e) / (a (1 - e)).
  const double v_p = std::sqrt(kMuEarth * (1.0 + kE) / r_p);
  const double inc = 51.6 * kDegToRad;
  return {{r_p, 0.0, 0.0}, {0.0, v_p * std::cos(inc), v_p * std::sin(inc)}};
}

double Period() {
  return 2.0 * std::numbers::pi * std::sqrt(kA * kA * kA / kMuEarth);
}

State TwoBody(double /*t*/, const State& y) {
  return TwoBodyDerivative(y, kMuEarth);
}

// Position error [km] after one period, using n_steps RK4 steps.
double OneOrbitError(int n_steps) {
  const State y0 = PerigeeState();
  const State y1 = PropagateRk4(y0, 0.0, Period() / n_steps, n_steps, TwoBody);
  return Norm(y1.r - y0.r);
}

}  // namespace

TEST_CASE("Initial energy matches -mu/(2a)", "[rk4]") {
  REQUIRE_THAT(SpecificEnergy(PerigeeState(), kMuEarth),
               WithinRel(-kMuEarth / (2.0 * kA), 1e-13));
}

TEST_CASE("RK4 conserves energy and angular momentum over 10 orbits", "[rk4]") {
  const State y0 = PerigeeState();
  const int n_steps = 10 * 1000;
  const State y1 = PropagateRk4(y0, 0.0, Period() / 1000, n_steps, TwoBody);

  // Prototype: 2.3e-11 relative energy error, 1.1e-11 relative |dh|.
  REQUIRE_THAT(SpecificEnergy(y1, kMuEarth),
               WithinRel(SpecificEnergy(y0, kMuEarth), 1e-10));

  const Vec3 h0 = SpecificAngularMomentum(y0);
  const Vec3 h1 = SpecificAngularMomentum(y1);
  REQUIRE(Norm(h1 - h0) / Norm(h0) < 1e-10);
}

TEST_CASE("RK4 converges at fourth order", "[rk4]") {
  const double order = std::log2(OneOrbitError(800) / OneOrbitError(1600));
  // Prototype: 4.04.
  REQUIRE_THAT(order, WithinAbs(4.0, 0.1));
}