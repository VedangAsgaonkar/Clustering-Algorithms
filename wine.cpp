#include <iostream>
#include <map>
#include <iterator>
#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>
#include "include/util/point.hpp"
#include "include/cluster/kMeansEstimator.hpp"
#include "include/plotter/plotter.hpp"

int main()
{
    srand48(12);

    point *point_list = new point[150];
    std::fstream infile1;
    std::fstream infile2;
    infile1.open("data/alc.csv", std::ios::in);
    infile2.open("data/hue.csv", std::ios::in);

    for(int i=0 ; i<150 ; i++)
    {
        std::string param1, param2;
        infile1 >> param1;
        infile2 >> param2;
        point_list[i].x = std::stof(param1);
        point_list[i].y = std::stof(param2);
    }

    
    std::cout << "type,x,y" << std::endl;
    kMeansEstimator *h = new kMeansEstimator(point_list, 150);
    std::multimap<int, int> mp = h->cluster(3, 20);
    for (auto i = mp.begin(); i != mp.end(); i++)
    {
        std::cout << i->first << "," << point_list[i->second].x << "," << point_list[i->second].y << std::endl;
    }
    plotter p(600, 600);
    p.createClusterPlot(point_list, 150);
    int labels[150];
    int index = 0;
    for (auto i = mp.begin(); i != mp.end(); i++)
    {
        labels[index] = i->first;
        index++;
    }
    p.labelClusterPlot(labels, 150);
    wait(5);
}