#ifndef _HIERARCHICALESTIMATOR_H_
#define _HIERARCHICALESTIMATOR_H_

#include "union_point.hpp"
#include "edge.hpp"
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
    hierarchicalEstimator(point *point_list, int n);
    hierarchicalEstimator(double *xlist, double *ylist, int n);
    std::multimap<int, int> cluster(int k) const;
    std::multimap<int, int> cluster(double epsilon) const;
    ~hierarchicalEstimator();
};

#endif