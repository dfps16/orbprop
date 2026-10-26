#pragma once

#include "orbprop/vec3.hpp"

// This state type only has what we strictly want

namespace orbprop {
    // Translational state: position r [km] and velocity v [km/s].
    // Also used for the state's time derivative, where r holds dr/dt [km/s]
    // and v holds dv/dt [km/s^2].
    struct State {
        Vec3 r;
        Vec3 v;

        bool operator==(const State&) const = default; // this type can be compared
    };

constexpr State operator+(const State& a, const State& b) {
    return { a.r + b.r, a.v + b.v};
}

constexpr State operator*(double s, const State& x) {
    return { s * x.r, s * x.v};
}
} // namespace orbprop