#include "orbprop/dynamics.hpp"

#include <cassert>
#include <cmath>

namespace orbprop {
    double CircularVelocity(double r, double mu) {
        return std::sqrt(mu / r);
    }

    Vec3 TwoBodyAcceleration(const Vec3& r, double mu) {
        const double r_norm = Norm(r);
        assert(r_norm > 0.0 && "position must be non-zero"); // ensure no NaN
        const double r_cubed = r_norm * r_norm * r_norm;
        return (-mu / r_cubed) * r;
    }
} // namespace orbprop