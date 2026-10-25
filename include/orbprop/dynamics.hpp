#pragma once

namespace orbprop {
    // Speed of a circular orbit of radius r [km]
    // About a body with grav param mu [km^3/s^2]
    // Returns km/s
    double CircularVelocity(double r, double mu);
}