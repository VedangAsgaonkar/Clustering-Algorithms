#include "matrix2.hpp"

matrix2::matrix2()
{
}

matrix2::matrix2(double a00, double a01, double a10, double a11)
{
    a[0][0] = a00;
    a[0][1] = a01;
    a[1][0] = a10;
    a[1][1] = a11;
}

double matrix2::determinant() const
{
    return a[0][0] * a[1][1] - a[1][0] * a[0][1];
}

matrix2 matrix2::inverse() const
{
    if (this->determinant() != 0)
    {
        return matrix2(a[1][1],-a[1][0],-a[0][1],a[0][0])/this->determinant();
    }
    else
    {
        return matrix2();
    }
}