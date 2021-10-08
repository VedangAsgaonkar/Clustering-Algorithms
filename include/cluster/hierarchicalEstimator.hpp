#ifndef _HIERARCHICALESTIMATOR_H_
#define _HIERARCHICALESTIMATOR_H_

#include "include/util/union_point.hpp"
#include "include/util/edge.hpp"
#include <map>
#include <queue>
#include <functional>

class hierarchicalEstimator
{
private:
    union_point *union_point_list;
    int n;
    std::priority_queue<edge, std::vector<edge>, std::function<bool(edge &, edge &)>> edge_list;

public:
    /**
     * @brief Construct a new hierarchical Estimator object
     * 
     * @param point_list array of data points
     * @param n number of points
     */
    hierarchicalEstimator(point *point_list, int n);

    /**
     * @brief Construct a new hierarchical Estimator object
     * 
     * @param xlist array of x-coordinates of data points
     * @param ylist array of y-coordinates of data points
     * @param n number of points
     */
    hierarchicalEstimator(double *xlist, double *ylist, int n);

    /**
     * @brief Perform hierarchical clustering
     * 
     * @param k number of clusters
     * @return std::multimap<int, int> 
     */
    std::multimap<int, int> cluster(int k) const;

    /**
     * @brief Perform hierarchical clustering
     * 
     * @param epsilon minimum seperation between clusters
     * @return std::multimap<int, int> 
     */
    std::multimap<int, int> cluster(double epsilon) const;

    /**
     * @brief Destroy the hierarchical Estimator object
     * 
     */
    ~hierarchicalEstimator();
};

#endif