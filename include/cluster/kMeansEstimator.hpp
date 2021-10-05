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
    kMeansEstimator(point *point_list, int n);
    kMeansEstimator(double *xlist, double *ylist, int n);
    std::multimap<int,int> cluster(int k, int iter) const;
    ~kMeansEstimator();
};

#endif