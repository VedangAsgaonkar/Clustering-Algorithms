#ifndef _KMEANSESTIMATOR_H_
#define _KMEANSESTIMATOR_H_

#include "include/util/point.hpp"
#include<map>

class kMeansEstimator
{
private:
    point *point_list;
    int n;
    bool created_list;

public:
    /**
     * @brief Construct a new k Means Estimator object
     * 
     * @param point_list array of data points
     * @param n number of points
     */
    kMeansEstimator(point *point_list, int n);

    /**
     * @brief Construct a new k Means Estimator object
     * 
     * @param xlist array of x-coordinates of data points
     * @param ylist array of y-coordinates of data points
     * @param n number of points
     */
    kMeansEstimator(double *xlist, double *ylist, int n);

    /**
     * @brief Perform k means clustering
     * 
     * @param k k value
     * @param iter number of iterations
     * @return std::multimap<int,int> multimap of cluster number to point index
     */
    std::multimap<int,int> cluster(int k, int iter) const;

    /**
     * @brief Destroy the k Means Estimator object
     * 
     */
    ~kMeansEstimator();
};

#endif