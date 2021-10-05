#ifndef _PLOTTER_H_
#define _PLOTTER_H_

#include <simplecpp>
#include <map>
#include <unordered_map>
#include <vector>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include "include/util/point.hpp"

void makecanvas(int xdim, int ydim, bool &start, std::condition_variable &cv_creation, bool &stop, std::condition_variable &cv_destruction, std::unique_lock<std::mutex> &lck_destruction);

class plotter
{
private:
    int xdim;
    int ydim;
    std::thread guiThread;
    Circle *data;
    std::unordered_map<int, int> colors;
    std::mutex mtx_creation;
    std::unique_lock<std::mutex> lck_creation;
    std::mutex mtx_destruction;
    std::unique_lock<std::mutex> lck_destruction;

public:
    bool start;
    bool stop;
    bool resume;
    std::condition_variable cv_creation;
    std::condition_variable cv_destruction;
    plotter(int xdim, int ydim);
    void createClusterPlot(point *point_list, int n);
    void labelClusterPlot(std::string *labels, int n);
    void clear();
    ~plotter();
};

#endif