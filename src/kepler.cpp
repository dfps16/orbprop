#include "orbprop/kepler.hpp"

#include <cmath>

#include "orbprop/state.hpp"
#include "orbprop/vec3.hpp"

namespace orbprop {
State KeplerianToCartesian(const KeplerElements& k, double mu) {
  double lambda_true = 0.0;  // True longitude
  double u = 0.0;            // Argument of latitude
  double longp_true = 0.0;   // True Longitude of periapsis
  double argp = 0.0;         // Temporary argp
  double raan = 0.0;         // Temporary raan
  double nu = 0.0;           // Temporary true anomaly
  double p = 0.0;            // Semi-latus rectum
  p = k.a * (1 - k.e * k.e);

  if (k.e == 0 && k.i == 0) {
    // Circular equatorial case
    argp, raan = 0.0;
    lambda_true = k.nu + k.raan + k.argp;  // Approximation from Vallado
    nu = lambda_true;
  } else if (k.e == 0) {
    // Circular inclined case
    argp = 0.0;
    u = k.nu + k.argp;
    nu = u;
  } else if (k.i == 0) {
    // Elliptical equatorial case
    raan = 0.0;
    longp_true = k.raan + k.argp;  // Approximation valid for small inclination
    argp = longp_true;
  } else {
    // Elliptical non-equatorial cases
    argp = k.argp;
    raan = k.raan;
    nu = k.nu;
  }
}


}  // namespace orbprop