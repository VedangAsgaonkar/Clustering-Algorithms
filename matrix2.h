#ifndef _MATRIX2_H_
#define _MATRIX2_H_

#include <iostream>


class matrix2
{
public:
    matrix2();
    matrix2(double a00, double a01, double a10, double a11);
    double determinant() const;
    matrix2 inverse() const;
    double a[2][2];
};

inline std::istream &operator>>(std::istream &is, matrix2 &m)
{
    is >> m.a[0][0] >> m.a[0][1] >> m.a[1][0] >> m.a[1][1];
    return is;
}
inline std::ostream &operator<<(std::ostream &os, matrix2 &m)
{
    os << m.a[0][0] << m.a[0][1] << "\n"
       << m.a[1][0] << m.a[1][1];
    return os;
}

inline matrix2 operator+(const matrix2 &m1, const matrix2 &m2)
{
    return matrix2(m1.a[0][0] + m2.a[0][0], m1.a[0][1] + m2.a[0][1], m1.a[1][0] + m2.a[1][0], m1.a[1][1] + m2.a[1][1]);
}
inline matrix2 operator-(const matrix2 &m1, const matrix2 &m2)
{
    return matrix2(m1.a[0][0] - m2.a[0][0], m1.a[0][1] - m2.a[0][1], m1.a[1][0] - m2.a[1][0], m1.a[1][1] - m2.a[1][1]);
}
inline matrix2 operator*(const matrix2 &m1, const matrix2 &m2)
{
    return matrix2(m1.a[0][0] * m2.a[0][0] + m1.a[0][1] * m2.a[1][0], m1.a[0][0] * m2.a[0][1] + m1.a[0][1] * m2.a[1][1], m1.a[1][0] * m2.a[0][0] + m1.a[1][1] * m2.a[1][0], m1.a[1][1] * m2.a[1][1] + m1.a[1][0] * m2.a[0][1]);
}
inline matrix2 operator*(const matrix2 &m1, double t)
{
    return matrix2(m1.a[0][0] * t, m1.a[0][1] * t, m1.a[1][0] * t, m1.a[1][1] * t);
}
inline matrix2 operator/(const matrix2 &m1, double t)
{
    return matrix2(m1.a[0][0] / t, m1.a[0][1] / t, m1.a[1][0] / t, m1.a[1][1] / t);
}

#endif