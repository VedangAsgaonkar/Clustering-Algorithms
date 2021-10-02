#include <iostream>
#include <map>
#include <iterator>
#include <cmath>
#include "point.h"
#include "kMeansEstimator.h"
#include "densityBasedEstimator.h"

int main()
{
    srand48(12);
    double *x_list = new double[300];
    double *y_list = new double[300];
    for (int i = 0; i < 300; i++)
    {
        if (i < 200)
        {
            double theta = 6.28*drand48();
            x_list[i] = 5*cos(theta);
            y_list[i] = 5*sin(theta);
        }
        else if (i < 300)
        {
            double theta = 3.14/3 + 3.14*drand48()/3;
            x_list[i] = -3*cos(theta);
            y_list[i] = -3*sin(theta);
        }
    }
    std::cout << "type,x,y" << std::endl;
    // kMeansEstimator *k = new kMeansEstimator(x_list, y_list, 400);
    // std::multimap<int, int> mp = k->cluster(4, 20);
    densityBasedEstimator *d = new densityBasedEstimator(x_list,y_list,300,1);
    std::multimap<int, int> mp = d->cluster(3);
    for (auto i = mp.begin(); i != mp.end(); i++)
    {
        std::cout << i->first << "," <<x_list[i->second] << "," << y_list[i->second] << std::endl;
    }
}