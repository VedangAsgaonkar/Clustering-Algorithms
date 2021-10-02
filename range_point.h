#ifndef _RANGE_POINT_H_
#define _RANGE_POINT_H_

#include "point.h"
#include<unordered_set>

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