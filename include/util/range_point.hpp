#ifndef _RANGE_POINT_H_
#define _RANGE_POINT_H_

#include "include/util/point.hpp"
#include<unordered_set>

/**
 * @brief Extends point to allow for storing neighbours
 * 
 */
class range_point : public point{
public:
    std::unordered_set<range_point*> neighbours;
    int num_neighbours;
    bool clustered;
    int index;
    range_point();
    range_point(double x, double y);
    range_point(double x, double y, std::string label);
};

#endif