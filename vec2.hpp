#ifndef _VEC2_H_
#define _VEC2_H_

#include <cstdlib>
#include <iostream>

#include "matrix2.hpp"

class vec2
{
public:
    vec2();
    vec2(double e0, double e1);
    double x() const;
    double y() const;
    double length() const;
    double squared_length() const;
    double e[2];
};

inline std::istream &operator>>(std::istream &is, vec2 &t)
{
    is >> t.e[0] >> t.e[1];
    return is;
}
inline std::ostream &operator<<(std::ostream &os, vec2 &t)
{
    os << t.e[0] << " " << t.e[1];
    return os;
}

inline vec2 operator+(const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1]);
}
inline vec2 operator-(const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1]);
}
inline vec2 operator*(const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1]);
}
inline vec2 operator/(const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1]);
}
inline vec2 operator*(const vec2 &v1, double t)
{
    return vec2(v1.e[0] * t, v1.e[1] * t);
}
inline vec2 operator/(const vec2 &v1, double t)
{
    return vec2(v1.e[0] / t, v1.e[1] / t);
}
inline double dot(const vec2 &v1, const vec2 &v2)
{
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1];
}
inline matrix2 outer_product(const vec2 &v1, const vec2 &v2)
{
    return matrix2(v1.e[0] * v2.e[0], v1.e[0] * v2.e[1], v1.e[1] * v2.e[0], v1.e[1] * v2.e[1]);
}
inline vec2 operator*(const matrix2 &m1, const vec2 &v1)
{
    return vec2(m1.a[0][0] * v1.e[0] + m1.a[0][1] * v1.e[1], m1.a[1][0] * v1.e[0] + m1.a[1][1] * v1.e[1]);
}
inline vec2 unit_vector(vec2 v)
{
    return v / v.length();
}

#endif