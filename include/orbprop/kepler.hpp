#pragma once

#include "orbprop/state.hpp"

namespace orbprop {
// Keplerian orbital elements (a, e, i, raan, argp, nu)
struct KeplerElements {
  double a = 0.0;  // Semi-major axis [km]
  double e = 0.0;  // Eccentricity [nd] (0 < e < 1)
  double i = 0.0;  // Inclination [rad] (i =/= 0)
  double raan =
      0.0;  // Right Ascension of the Ascending Node [rad] (0 < raan < 2pi)
  double argp = 0.0;  // Argument of periapsis [rad] (0 < raan < 2pi)
  double nu = 0.0;    // True Anomaly [rad] (0 < raan < 2pi)
};
State KeplerianToCartesian(const KeplerElements&, double mu);

KeplerElements CartasianToKeplerian(const State&, double mu);

}  // namespace orbprop
