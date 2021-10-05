#include "hierarchicalEstimator.hpp"

hierarchicalEstimator::hierarchicalEstimator(point *point_list, int n)
{
    this->union_point_list = new union_point[n];
    this->n = n;
    edge_list = std::priority_queue<edge, std::vector<edge>, std::function<bool(edge &, edge &)>>(CompareEdge);
    for (int i = 0; i < n; i++)
    {
        this->union_point_list[i].x = union_point_list[i].x;
        this->union_point_list[i].y = union_point_list[i].y;
        this->union_point_list[i].label = union_point_list[i].label;
        this->union_point_list[i].cluster_number = i;
        for (int j = 0; j < i; j++)
        {
            edge_list.push(edge(&union_point_list[i], &union_point_list[j]));
        }
    }
}

hierarchicalEstimator::hierarchicalEstimator(double *xlist, double *ylist, int n)
{
    this->union_point_list = new union_point[n];
    this->n = n;
    edge_list = std::priority_queue<edge, std::vector<edge>, std::function<bool(edge &, edge &)>>(CompareEdge);
    for (int i = 0; i < n; i++)
    {
        this->union_point_list[i].x = xlist[i];
        this->union_point_list[i].y = ylist[i];
        this->union_point_list[i].cluster_number = i;
        for (int j = 0; j < i; j++)
        {
            edge_list.push(edge(&union_point_list[i], &union_point_list[j]));
        }
    }
}

std::multimap<int, int> hierarchicalEstimator::cluster(int k) const
{
    std::priority_queue<edge, std::vector<edge>, std::function<bool(edge &, edge &)>> edges = edge_list;
    int i = 0;
    // std::cout << n<< std::endl;

    while (i < n - k)
    {
        // std::cout << i << std::endl;
        edge e = edges.top();
        edges.pop();
        union_point *ptr1 = e.first;
        union_point *ptr2 = e.second;
        if (ptr1->find() != ptr2->find())
        {
            merge(ptr1, ptr2);
            i++;
        }
    }
    std::multimap<int, int> clusters;
    for (int j = 0; j < n; j++)
    {
        clusters.insert(std::pair<int, int>(union_point_list[j].find(), j));
    }
    return clusters;
}

std::multimap<int, int> hierarchicalEstimator::cluster(double epsilon) const
{
    std::priority_queue<edge, std::vector<edge>, std::function<bool(edge &, edge &)>> edges = edge_list;
    while (edges.top().length < epsilon)
    {
        edge e = edges.top();
        edges.pop();
        union_point *ptr1 = e.first;
        union_point *ptr2 = e.second;
        if (ptr1->find() != ptr2->find())
        {
            merge(ptr1, ptr2);
        }
    }
    std::multimap<int, int> clusters;
    for (int j = 0; j < n; j++)
    {
        clusters.insert(std::pair<int, int>(union_point_list[j].find(), j));
    }
    return clusters;
}

hierarchicalEstimator::~hierarchicalEstimator()
{
    delete[] union_point_list;
}