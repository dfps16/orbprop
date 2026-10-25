#include "orbprop/dynamics.hpp"

#include <cmath>

namespace orbprop {
    double CircularVelocity(double r, double mu) {
        return std::sqrt(mu / r);
    }
}