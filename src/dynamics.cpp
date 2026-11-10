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

    State TwoBodyDerivative(const State& s, double mu) {
        return {s.v, TwoBodyAcceleration(s.r, mu)};
    }

    double SpecificEnergy(const State& s, double mu) {
        return 0.5 * Dot(s.v, s.v) - mu / Norm(s.r);
    }

    Vec3 SpecificAngularMomentum(const State& s) { 
        return Cross(s.r, s.v); 
    }
} // namespace orbprop