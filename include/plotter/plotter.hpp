
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

    /**
     * @brief Construct a new plotter object
     * 
     * @param xdim width of the plotter window
     * @param ydim height of the plotter window
     */
    plotter(int xdim, int ydim);

    /**
     * @brief Create a Cluster Plot object
     * 
     * @param point_list array of points to plot
     * @param n number of points
     */
    void createClusterPlot(point *point_list, int n);

    /**
     * @brief Provide labels to points to allow color-coding
     * 
     * @param labels array of labels
     * @param n number of labels
     */
    void labelClusterPlot(std::string *labels, int n);

    /**
     * @brief Provide labels to points to allow color-coding
     * 
     * @param labels array of labels
     * @param n number of labels
     */
    void labelClusterPlot(int *labels, int n);

    /**
     * @brief Clear the plot
     * 
     */
    void clear();

    /**
     * @brief Destroy the plotter object
     * 
     */
    ~plotter();
};

#endif