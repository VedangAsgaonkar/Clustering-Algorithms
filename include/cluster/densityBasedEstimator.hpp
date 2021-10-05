#ifndef _DENSITY_BASED_ESTIMATOR_H_
#define _DENSITY_BASED_ESTIMATOR_H_

#include "include/util/range_point.hpp"
#include <map>

class densityBasedEstimator
{
private:
    range_point *point_list;
    int n;
    double epsilon;

public:
    densityBasedEstimator(point *point_list, int n, double epsilon);
    densityBasedEstimator(double *xlist, double *ylist, int n, double epsilon);
    std::multimap<int, int> cluster(int min_pts) const;
    ~densityBasedEstimator();
};

#endif