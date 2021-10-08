#include "include/cluster/densityBasedEstimator.hpp"
#include "include/plotter/plotter.hpp"
#include <queue>
#include <iterator>
#include <tuple>
#include <iostream>

densityBasedEstimator::densityBasedEstimator(point *point_list, int n, double epsilon)
{
    this->point_list = new range_point[n];
    this->n = n;
    this->epsilon = epsilon;
    for (int i = 0; i < n; i++)
    {
        this->point_list[i].x = point_list[i].x;
        this->point_list[i].y = point_list[i].y;
        this->point_list[i].label = point_list[i].label;
        this->point_list[i].index = i;
        for (int j = 0; j < i; j++)
        {
            if (distance(this->point_list[j], this->point_list[i]) <= epsilon)
            {
                this->point_list[i].num_neighbours++;
                this->point_list[i].neighbours.insert(&this->point_list[j]);
                this->point_list[j].num_neighbours++;
                this->point_list[j].neighbours.insert(&this->point_list[i]);
            }
        }

    }
}

densityBasedEstimator::densityBasedEstimator(double *xlist, double *ylist, int n, double epsilon)
{
    this->point_list = new range_point[n];
    this->n = n;
    this->epsilon = epsilon;
    for (int i = 0; i < n; i++)
    {
        this->point_list[i].x = xlist[i];
        this->point_list[i].y = ylist[i];
        this->point_list[i].index = i;
        for (int j = 0; j < i; j++)
        {
            if (distance(this->point_list[j], this->point_list[i]) <= epsilon)
            {
                this->point_list[i].num_neighbours++;
                this->point_list[i].neighbours.insert(&this->point_list[j]);
                this->point_list[j].num_neighbours++;
                this->point_list[j].neighbours.insert(&this->point_list[i]);
            }
        }
    }
}

std::multimap<int, int> densityBasedEstimator::cluster(int min_pts) const
{
    std::multimap<int, int> clusters;
    int k = 0;
    plotter pl(400, 400);
    point *aux_point_list = new point[n];
    for(int i=0 ; i<n ; i++)
    {
        aux_point_list[i].x = point_list[i].x;
        aux_point_list[i].y = point_list[i].y;
    }
    pl.createClusterPlot(aux_point_list, n);

    for (int i = 0; i < n; i++)
    {
        if (!point_list[i].clustered)
        {
            std::queue<int> q;
            q.push(i);
            point_list[i].clustered = true;
            while (!q.empty())
            {
                int p = q.front();
                clusters.insert(std::pair<int, int>(k, p));
                q.pop();
                if (point_list[p].num_neighbours >= min_pts)
                {
                    for (auto &u : point_list[p].neighbours)
                    {
                        if (!u->clustered)
                        {
                            u->clustered = true;
                            q.push(u->index);
                        }
                    }
                }
                int labels[n];
                int index = 0;
                for (auto i = clusters.begin(); i != clusters.end(); i++)
                {
                    labels[index] = i->first;
                    index++;
                }
                pl.labelClusterPlot(labels, index);
            }
            k++;
        }
    }
    delete[] aux_point_list;
    wait(5);
    return clusters;
}

densityBasedEstimator::~densityBasedEstimator()
{
    delete[] point_list;
}
