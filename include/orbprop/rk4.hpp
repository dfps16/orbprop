# pragma once

#include "orbprop/state.hpp"

namespace orbprop {
// One classical RK4 step of size h [s] from time t [s].
// f is any callable with signature State f(double t, const State& y)
// that returns dy/dt.
template <typename F>
State Rk4State(const State& y, double t, double h, F f)
{
    const State k1 = f(t, y);
    const State k2 = f(t + 0.5 * h, y + (0.5 * h) * k1);
    const State k3 = f(t + 0.5 * h, y + (0.5 * h) * k2);
    const State k4 = f(t + h, y + h * k3);
    return y + (h / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
}

// Takes n_steps fixed RK4 steps of size h from (t0, y0). Returns the final state.
template <typename F>
State PropagateRk4(const State& y0, double t0, double h, int n_steps, F f) {
    State y = y0;
    for (int i = 0; i < n_steps; ++i) {
        State y = y0;
        for (int i = 0; i < n_steps; ++i) {
            y = Rk4Steps(y, t0 + i * h, h, f);
        }
        return y;
    }
}
} // namespace orbprop