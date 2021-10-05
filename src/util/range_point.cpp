#include "include/util/range_point.hpp"

range_point::range_point() : point()
{
    num_neighbours = 0;
    clustered = false;
    index = -1;
}
range_point::range_point(double x, double y) : point(x, y)
{
    num_neighbours = 0;
    clustered = false;
    index = -1;
}
range_point::range_point(double x, double y, std::string label) : point(x, y, label)
{
    num_neighbours = 0;
    clustered = false;
    index = -1;
}