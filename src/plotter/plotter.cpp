#include "include/plotter/plotter.hpp"
#include <string>
#include <sstream>

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
    // Line x_axis(0, ydim / 2, xdim, ydim / 2);
    // Line y_axis(xdim / 2, 0, xdim / 2, ydim);
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
    double x_min = INFINITY;
    double x_max = -INFINITY;
    double y_min = INFINITY;
    double y_max = -INFINITY;

    for (int i = 0; i < n; i++)
    {
        if (point_list[i].x < x_min)
        {
            x_min = point_list[i].x;
        }
        if (point_list[i].x > x_max)
        {
            x_max = point_list[i].x;
        }
        if (point_list[i].y < y_min)
        {
            y_min = point_list[i].y;
        }
        if (point_list[i].y > y_max)
        {
            y_max = point_list[i].y;
        }
    }
    xaxis = new Line(0, 19 * ydim / 20, 19 * xdim / 20, 19 * ydim / 20);
    yaxis = new Line(xdim / 20, ydim / 20, xdim / 20, ydim);
    xlabel = new Text(19 * xdim / 20, 39 * ydim / 40, "x");
    ylabel = new Text(xdim / 40, ydim / 40, "y");
    xticks = new Line[9];
    yticks = new Line[9];
    xscales = new Text[9];
    yscales = new Text[9];
    data = new Circle[n];
    for (int i = 0; i < n; i++)
    {
        double x = (this->xdim / 10.0) + (8 * this->xdim / 10.0) * ((point_list[i].x - x_min) / (x_max - x_min));
        double y = (this->ydim / 10.0) + (8 * this->ydim / 10.0) * ((y_max - point_list[i].y) / (y_max - y_min));
        data[i] = Circle(x, y, 6);
        data[i].setFill(true);
    }
    for (int i = 1; i <= 9; i++)
    {
        std::ostringstream ss1, ss2;
        ss1.precision(2);
        ss2.precision(2);
        ss1 << std::fixed << x_min + (i - 1) * (x_max - x_min) * 8;
        ss2 << std::fixed << y_min + (i - 1) * (y_max - y_min) * 8;
        xticks[i - 1] = Line(i * xdim / 10, 19 * ydim / 20, i * xdim / 10, 39 * ydim / 40);
        yticks[i - 1] = Line(xdim / 40, (10 - i) * ydim / 10, xdim / 20, (10 - i) * ydim / 10);
        xscales[i - 1] = Text(i * xdim / 10, 39 * ydim / 40, ss1.str());
        yscales[i - 1] = Text(xdim / 40, (10 - i) * ydim / 10, ss2.str());
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

void plotter::labelClusterPlot(int *labels, int n)
{
    int cnt = 0;
    int curr_label = labels[0];
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
    delete xaxis;
    delete yaxis;
    delete xlabel;
    delete ylabel;
    delete[] xticks;
    delete[] yticks;
    delete[] xscales;
    delete[] yscales;
    resume = true;
}

plotter::~plotter()
{
    delete[] data;
    delete xaxis;
    delete yaxis;
    delete xlabel;
    delete ylabel;
    delete[] xticks;
    delete[] yticks;
    delete[] xscales;
    delete[] yscales;
    stop = true;
    cv_destruction.notify_all();
    guiThread.join();
}
