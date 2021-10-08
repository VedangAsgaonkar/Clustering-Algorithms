#include <iostream>
#include <map>
#include <iterator>
#include <cmath>
#include <cstdlib>
#include "include/util/point.hpp"
#include "include/cluster/kMeansEstimator.hpp"
#include "include/cluster/densityBasedEstimator.hpp"
#include "include/cluster/gaussianEstimator.hpp"
#include "include/cluster/hierarchicalEstimator.hpp"
#include "include/plotter/plotter.hpp"

int main()
{
    srand48(12);
    double *x_list = new double[400];
    double *y_list = new double[400];
    point *point_list = new point[400];
    for (int i = 0; i < 400; i++)
    {
        if (i < 200)
        {
            double theta = 6.28 * drand48();
            x_list[i] = 5 * cos(theta);
            y_list[i] = 5 * sin(theta);
        }
        else if (i < 300)
        {
            double theta = (3.14 / 3) + (3.14 / 3) * drand48();
            x_list[i] = 3 * cos(theta);
            y_list[i] = -3 * sin(theta);
        }
        else if (i < 400)
        {
            double theta = (3.14 / 3) + (3.14 / 3) * drand48();
            x_list[i] = 3 * cos(theta);
            y_list[i] = 3 * sin(theta);
        }
        point_list[i].x = x_list[i];
        point_list[i].y = y_list[i];
    }
    std::cout << "type,x,y" << std::endl;
    densityBasedEstimator *h = new densityBasedEstimator(point_list, 400, 2);
    std::multimap<int, int> mp = h->cluster(2);
    for (auto i = mp.begin(); i != mp.end(); i++)
    {
        std::cout << i->first << "," << x_list[i->second] << "," << y_list[i->second] << std::endl;
    }
    plotter p(400, 400);
    p.createClusterPlot(point_list, 400);
    int labels[400];
    int index = 0;
    for (auto i = mp.begin(); i != mp.end(); i++)
    {
        labels[index] = i->first;
        index++;
    }
    p.labelClusterPlot(labels, 400);
    wait(5);
}