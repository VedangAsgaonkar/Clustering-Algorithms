#include "include/util/vec2.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

vec2::vec2()
{
}

vec2::vec2(double e0, double e1)
{
    this->e[0] = e0;
    this->e[1] = e1;
}

double vec2::x() const
{
    return e[0];
}
double vec2::y() const
{
    return e[1];
}

double vec2::length() const
{
    return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}
double vec2::squared_length() const
{
    return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}