#include "include/util/edge.hpp"

edge::edge(union_point *first, union_point *second)
{
    this->first = first;
    this->second = second;
    this->length = distance(first, second);
}

bool CompareEdge(edge &e1, edge &e2)
{
    return e1.length > e2.length;
}