#pragma once

#include "orbprop/vec3.hpp"

namespace orbprop {
    // Speed of a circular orbit of radius r [km]
    // About a body with grav param mu [km^3/s^2]
    // Returns km/s
    double CircularVelocity(double r, double mu);

    // Point-mass gravitational acceleration a = -mu r / |r|^3.
    // r: position [km] relative to the central body's centre, must be non-zero.
    // mu: gravitational parameter [km^3/s^2]. Returns km/s^2.
    Vec3 TwoBodyAcceleration(const Vec3& r, double mu);
} // namespace orbprop