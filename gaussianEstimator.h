#ifndef _GAUSIANESTIMATOR_H_
#define _GAUSIANESTIMATOR_H_

#include"point.h"
#include"vec2.h"
#include"matrix2.h"
#include<map>

class gaussianEstimator
{
private:
    vec2 *vec_list;
    int n;
    double gaussianProbability(const vec2 &point ,const vec2& mean, const matrix2 &cov) const;
public:
    gaussianEstimator(point *point_list, int n);
    gaussianEstimator(double *xlist, double *ylist, int n); 
    std::multimap<int,int> cluster(int k, int iter) const;
    ~gaussianEstimator(); 
};

#endif