#pragma once // loads this just once

#include <cmath>

namespace orbprop {
    // A 3D Cartesian vector. Units are implied by the user
    struct Vec3 {
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        
        bool operator==(const Vec3&) const = default;
    };    

    constexpr Vec3 operator+(const Vec3& a, const Vec3& b) {
        return {a.x + b.x, a.y + b.y, a.z + b.z};
    };

    constexpr Vec3 operator-(const Vec3& a, const Vec3& b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
    };

    constexpr Vec3 operator-(const Vec3& v) { return {-v.x, -v.y, -v.z}; }

    constexpr Vec3 operator*(double s, const Vec3& v) {
    return {s * v.x, s * v.y, s * v.z};
    };

    constexpr Vec3 operator*(const Vec3& v, double s) { return s * v; }

    constexpr Vec3 operator/(const Vec3& v, double s) {
    return {v.x / s, v.y / s, v.z / s};
    };

    constexpr double Dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    constexpr Vec3 Cross(const Vec3& a, const Vec3& b) {
    return {a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x};
    }

    inline double Norm(const Vec3& v) { return std::sqrt(Dot(v, v)); }
    
} // namespace orbprop