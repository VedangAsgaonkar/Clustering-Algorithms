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
    /**
     * @brief Construct a new density Based Estimator object
     * 
     * @param point_list array of data points
     * @param n number of points
     * @param epsilon the maximum distance within which two points are considered neighbours
     */
    densityBasedEstimator(point *point_list, int n, double epsilon);

    /**
     * @brief Construct a new density Based Estimator object
     * 
     * @param xlist array of x-coordinates of data points
     * @param ylist array of y-coordinates of data points
     * @param n number of points
     * @param epsilon the maximum distance within which two points are considered neighbours
     */
    densityBasedEstimator(double *xlist, double *ylist, int n, double epsilon);

    /**
     * @brief Perform density based clustering
     * 
     * @param min_pts The minimum number of points in neighbourhood for a point to be considerd a core point
     * @return std::multimap<int, int> 
     */
    std::multimap<int, int> cluster(int min_pts) const;

    /**
     * @brief Destroy the density Based Estimator object
     * 
     */
    ~densityBasedEstimator();
};

#endif