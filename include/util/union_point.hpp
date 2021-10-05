#ifndef _UNION_POINT_H_
#define _UNION_POINT_H_

#include "include/util/point.hpp"
#include <string>
#include<cmath>

class union_point : public point
{
public:
    union_point *parent;
    int cluster_number;
    int height;
    union_point();
    union_point(double x, double y, int cluster_number);
    union_point(double x, double y, std::string label, int cluster_number);
    int find() const;
};

inline void merge(union_point *p1, union_point *p2)
{
    union_point *ptr1 = p1;
    union_point *ptr2 = p2;
    while (ptr1->parent != nullptr)
    {
        ptr1 = ptr1->parent;
    }
    while (ptr2->parent != nullptr)
    {
        ptr2 = ptr2->parent;
    }

    if (ptr1->cluster_number != ptr2->cluster_number)
    {
        if (ptr1->height >= ptr2->height)
        {
            union_point *t = ptr1;
            ptr1 = ptr2;
            ptr2 = t;
        }
        ptr1->parent = ptr2;
        ptr2->cluster_number = std::min(ptr1->cluster_number,ptr2->cluster_number);
        ptr2->height = std::max(ptr2->height, 1+ptr1->height);
    }
}

#endif