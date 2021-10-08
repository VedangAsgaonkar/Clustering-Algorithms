#ifndef _GAUSIANESTIMATOR_H_
#define _GAUSIANESTIMATOR_H_

#include"include/util/point.hpp"
#include"include/util/vec2.hpp"
#include"include/util/matrix2.hpp"
#include<map>

class gaussianEstimator
{
private:
    vec2 *vec_list;
    int n;
    double gaussianProbability(const vec2 &point ,const vec2& mean, const matrix2 &cov) const;
public:
    /**
     * @brief Construct a new gaussian Estimator object
     * 
     * @param point_list array of data points
     * @param n number of points
     */
    gaussianEstimator(point *point_list, int n);

    /**
     * @brief Construct a new gaussian Estimator object
     * 
     * @param xlist array of x-coordinates of data points
     * @param ylist array of y-coordinates of data points 
     * @param n number of points
     */
    gaussianEstimator(double *xlist, double *ylist, int n); 

    /**
     * @brief Perform gaussian clustering
     * 
     * @param k number of clusters
     * @param iter number of iterations
     * @return std::multimap<int,int> 
     */
    std::multimap<int,int> cluster(int k, int iter) const;

    /**
     * @brief Destroy the gaussian Estimator object
     * 
     */
    ~gaussianEstimator(); 
};

#endif