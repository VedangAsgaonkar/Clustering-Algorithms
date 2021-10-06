#include <iostream>
#include <map>
#include <iterator>
#include <cmath>
#include <cstdlib>
#include "include/util/point.hpp"
#include "include/cluster/kMeansEstimator.hpp"
// #include "include/cluster/densityBasedEstimator.hpp"
// #include "include/cluster/gaussianEstimator.hpp"
// #include "include/cluster/hierarchicalEstimator.hpp"
#include "include/plotter/plotter.hpp"

int main()
{
    srand48(12);
    double *x_list = new double[400];
    double *y_list = new double[400];
    point *point_list = new point[400];
    for (int i = 0; i < 400; i++)
    {
        if (i < 100)
        {
            x_list[i] = 220 + 100 * drand48();
            y_list[i] = 220 + 100 * drand48();
        }
        else if (i < 200)
        {
            x_list[i] = 380 - 100 * drand48();
            y_list[i] = 220 + 100 * drand48();
        }
        else if (i < 300)
        {
            x_list[i] = 220 + 100 * drand48();
            y_list[i] = 380 - 100 * drand48();
        }
        else
        {
            x_list[i] = 380 - 100 * drand48();
            y_list[i] = 380 - 100 * drand48();
        }
        point_list[i].x = x_list[i];
        point_list[i].y = y_list[i];
    }
    std::cout << "type,x,y" << std::endl;
    kMeansEstimator *h = new kMeansEstimator(x_list, y_list, 400);
    std::multimap<int, int> mp = h->cluster(3, 20);
    for (auto i = mp.begin(); i != mp.end(); i++)
    {
        std::cout << i->first << "," << x_list[i->second] << "," << y_list[i->second] << std::endl;
    }
    plotter p(600, 600);
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

    // initCanvas("Graph", 800, 800);
    // plotter p;
    // p.scatter(point_list,400);
    // Circle c[400];
    // for (int i = 0; i < 400; i++)
    // {
    //     c[i] = Circle(500 + 50* point_list[i].x, 500 + 50 * point_list[i].y, 3);
    // }
}