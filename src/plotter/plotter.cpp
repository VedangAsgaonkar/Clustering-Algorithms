#include "plotter.hpp"
#include <string>

plotter::plotter(int xdim, int ydim)
{
    this->xdim = xdim;
    this->ydim = ydim;
    colors =
        {
            {0, 0x5555ff},
            {1, 0x55ff55},
            {2, 0xff5555},
            {3, 0x55cccc},
            {4, 0xcc55cc},
            {5, 0xcccc55},
        };
    lck_creation = std::unique_lock<std::mutex>(mtx_creation);
    lck_destruction = std::unique_lock<std::mutex>(mtx_destruction);
    start = false;
    stop = false;
    resume = false;
    guiThread = std::thread(makecanvas, xdim, ydim, std::ref(start), std::ref(cv_creation), std::ref(stop), std::ref(cv_destruction), std::ref(lck_destruction));
}

void makecanvas(int xdim, int ydim, bool &start, std::condition_variable &cv_creation, bool &stop, std::condition_variable &cv_destruction, std::unique_lock<std::mutex> &lck_destruction)
{
    initCanvas("Plot", xdim, ydim);
    Line x_axis(0, ydim / 2, xdim, ydim / 2);
    Line y_axis(xdim / 2, 0, xdim / 2, ydim);
    start = true;
    cv_creation.notify_all();
    while (!stop)
    {
        cv_destruction.wait(lck_destruction);
    }
    stop = false;
}

void plotter::createClusterPlot(point *point_list, int n)
{
    while (!start && !resume)
    {
        cv_creation.wait(lck_creation);
    }
    start = false;
    data = new Circle[n];
    for (int i = 0; i < n; i++)
    {
        data[i] = Circle(point_list[i].x, point_list[i].y, 4);
        data[i].setFill(true);
    }
}

void plotter::labelClusterPlot(std::string *labels, int n)
{
    int cnt = 0;
    std::string curr_label = labels[0];
    data[0].setColor(colors[cnt]);
    for (int i = 1; i < n; i++)
    {
        if (curr_label != labels[i])
        {
            cnt++;
            curr_label = labels[i];
        }
        data[i].setColor(colors[cnt]);
    }
}

void plotter::clear()
{
    delete[] data;
    resume = true;
}

plotter::~plotter()
{
    delete[] data;
    stop = true;
    cv_destruction.notify_all();
    guiThread.join();
}
