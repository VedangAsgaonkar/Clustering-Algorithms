#ifndef _EDGE_H_
#define _EDGE_H_

#include "include/util/union_point.hpp"

/**
 * @brief Implements edge between two union points
 * 
 */
class edge
{
public:
    double length;
    union_point *first;
    union_point *second;
    edge(union_point *first, union_point *second);
};

bool CompareEdge(edge &e1, edge &e2);

#endif