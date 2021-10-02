#include "point.h"

point::point()
{
    x = 0;
    y = 0;
    label = "";
}

point::point(double x, double y)
{
    this->x = x;
    this->y = y;
    label = "";
}

point::point(double x, double y, std::string label)
{
    this->x = x;
    this->y = y;
    this->label = label;
}