#include "union_point.hpp"

union_point::union_point() : point()
{
    this->parent = nullptr;
    this->height = 0;
}

union_point::union_point(double x, double y, int cluster_number) : point(x, y)
{
    this->cluster_number = cluster_number;
    this->parent = nullptr;
    this->height = 0;
}

union_point::union_point(double x, double y, std::string label, int cluster_number) : point(x, y, label)
{
    this->cluster_number = cluster_number;
    this->parent = nullptr;
    this->height = 0;
}

int union_point::find() const
{
    const union_point *ptr = this;
    while (ptr->parent != nullptr)
    {
        ptr = ptr->parent;
    }
    return ptr->cluster_number;
}