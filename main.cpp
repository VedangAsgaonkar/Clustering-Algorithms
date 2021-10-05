#include <iostream>
#include <map>
#include <iterator>
#include <cmath>
#include <cstdlib>
#include "point.hpp"
#include "kMeansEstimator.hpp"
#include "densityBasedEstimator.hpp"
#include "gaussianEstimator.hpp"
#include "hierarchicalEstimator.hpp"
#include "plotter.hpp"

int main()
{
    srand48(12);
    double *x_list = new double[400];
    double *y_list = new double[400];
    for (int i = 0; i < 400; i++)
    {
        if (i < 100)
        {
            x_list[i] = -5 + 4 * drand48();
            y_list[i] = -5 + 4 * drand48();
        }
        else if (i < 200)
        {
            x_list[i] = 5 - 4 * drand48();
            y_list[i] = -5 + 4 * drand48();
        }
        else if (i < 300)
        {
            x_list[i] = -5 + 4 * drand48();
            y_list[i] = 5 - 4 * drand48();
        }
        else
        {
            x_list[i] = 5 - 4 * drand48();
            y_list[i] = 5 - 4 * drand48();
        }
    }
    std::cout << "type,x,y" << std::endl;
    // kMeansEstimator *k = new kMeansEstimator(x_list, y_list, 400);
    // std::multimap<int, int> mp = k->cluster(4, 20);
    // densityBasedEstimator *d = new densityBasedEstimator(x_list,y_list,300,1);
    // std::multimap<int, int> mp = d->cluster(3);
    hierarchicalEstimator *h = new hierarchicalEstimator(x_list, y_list, 400);
    std::multimap<int, int> mp = h->cluster(1.0);
    point *point_list = new point[400];
    int j=0;
    for (auto i = mp.begin(); i != mp.end(); i++)
    {
        point_list[j].x = x_list[i->second];
        point_list[j].y = y_list[i->second];
        point_list[j].label = to_string(i->first);
        j++;
        std::cout << i->first << "," << x_list[i->second] << "," << y_list[i->second] << std::endl;
    }
    initCanvas("Graph", 800, 800);
    plotter p;
    p.scatter(point_list,400);
    // Circle c[400];
    // for (int i = 0; i < 400; i++)
    // {
    //     c[i] = Circle(500 + 50* point_list[i].x, 500 + 50 * point_list[i].y, 3);
    // }
}