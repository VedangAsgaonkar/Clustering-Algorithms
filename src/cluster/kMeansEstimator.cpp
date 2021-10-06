#include "include/cluster/kMeansEstimator.hpp"
#include <map>
#include <iterator>
#include <tuple>
#include <vector>
#include "include/plotter/plotter.hpp"

kMeansEstimator::kMeansEstimator(point *point_list, int n)
{
    this->point_list = point_list;
    this->n = n;
    created_list = false;
}

kMeansEstimator::kMeansEstimator(double *xlist, double *ylist, int n)
{
    this->n = n;
    point_list = new point[n];
    for (int i = 0; i < n; i++)
    {
        point_list[i].x = xlist[i];
        point_list[i].y = ylist[i];
    }
    created_list = true;
}

std::multimap<int, int> kMeansEstimator::cluster(int k, int iter) const
{
    // int gd = DETECT, gm;
    // initgraph(&gd, &gm, NULL);

    std::vector<std::multimap<int, int>> set_clusters;
    std::vector<double> dispersions;
    int run_count = 3;
    plotter p(600, 600);
    for (int run = 0; run < run_count; run++)
    {
        if (run > 0)
        {
            p.clear();
        }
        p.createClusterPlot(point_list, n);
        double max_x = point_list[0].x;
        double min_x = point_list[0].x;
        double max_y = point_list[0].y;
        double min_y = point_list[0].y;
        for (int i = 1; i < n; i++)
        {
            if (max_x < point_list[i].x)
            {
                max_x = point_list[i].x;
            }
            if (max_y < point_list[i].y)
            {
                max_y = point_list[i].y;
            }
            if (min_x > point_list[i].x)
            {
                min_x = point_list[i].x;
            }
            if (min_y > point_list[i].y)
            {
                min_y = point_list[i].y;
            }
        }

        // randomly initialize the means
        point *means = new point[k];
        for (int i = 0; i < k; i++)
        {
            means[i].x = min_x + (max_x - min_x) * drand48();
            means[i].y = min_y + (max_y - min_y) * drand48();
        }

        // initialize the clusters
        std::multimap<int, int> clusters;
        for (int i = 0; i < n; i++)
        { // for each point
            int cluster = 0;
            double dist = distance(point_list[i], means[0]);
            for (int j = 1; j < k; j++)
            { // for each mean
                double dist2 = distance(point_list[i], means[j]);
                if (dist2 < dist)
                {
                    dist = dist2;
                    cluster = j;
                }
            }
            clusters.insert(std::pair<int, int>(cluster, i));
        }
        // update the means
        for (int i = 0; i < k; i++)
        {
            auto itr1 = clusters.lower_bound(i);
            auto itr2 = clusters.upper_bound(i);
            double x_sum = 0;
            double y_sum = 0;
            int cnt = 0;

            while (itr1 != itr2)
            {
                if (itr1->first == i)
                {
                    x_sum += point_list[itr1->second].x;
                    y_sum += point_list[itr1->second].y;
                    cnt++;
                }
                itr1++;
            }
            if (cnt != 0)
            {
                means[i].x = x_sum / cnt;
                means[i].y = y_sum / cnt;
            }
        }

        // iterations
        for (int t = 0; t < iter; t++)
        {
            // deleting clusters
            clusters.erase(clusters.begin(), clusters.end());

            for (int i = 0; i < n; i++)
            { // for each point
                int cluster = 0;
                double dist = distance(point_list[i], means[0]);
                for (int j = 1; j < k; j++)
                { // for each mean
                    double dist2 = distance(point_list[i], means[j]);
                    if (dist2 < dist)
                    {
                        dist = dist2;
                        cluster = j;
                    }
                }
                clusters.insert(std::pair<int, int>(cluster, i));
            }
            // update the means
            for (int i = 0; i < k; i++)
            {
                auto itr1 = clusters.lower_bound(i);
                auto itr2 = clusters.upper_bound(i);
                double x_sum = 0;
                double y_sum = 0;
                int cnt = 0;

                while (itr1 != itr2)
                {
                    if (itr1->first == i)
                    {
                        x_sum += point_list[itr1->second].x;
                        y_sum += point_list[itr1->second].y;
                        cnt++;
                    }
                    itr1++;
                }
                if (cnt != 0)
                {
                    means[i].x = x_sum / cnt;
                    means[i].y = y_sum / cnt;
                }
            }
            int labels[n];
            int index = 0;
            for (auto i = clusters.begin(); i != clusters.end(); i++)
            {
                labels[index] = i->first;
                index++;
            }
            p.labelClusterPlot(labels,n);
            wait(0.5);
        }

        // find WCSS
        double wcss = 0;
        for (int i = 0; i < k; i++)
        {
            auto itr1 = clusters.lower_bound(i);
            auto itr2 = clusters.upper_bound(i);
            double x_sum = 0;
            double y_sum = 0;

            while (itr1 != itr2)
            {
                if (itr1->first == i)
                {
                    x_sum += (point_list[itr1->second].x - means[i].x) * (point_list[itr1->second].x - means[i].x);
                    y_sum += (point_list[itr1->second].y - means[i].y) * (point_list[itr1->second].y - means[i].y);
                }
                itr1++;
            }
            wcss += x_sum + y_sum;
        }
        dispersions.push_back(wcss);
        set_clusters.push_back(clusters);
    }

    int index = 0;
    double min_wcss = dispersions[index];
    for (int i = 0; i < run_count; i++)
    {
        if (dispersions[i] < min_wcss)
        {
            min_wcss = dispersions[i];
            index = i;
        }
    }
    return set_clusters[index];
}

kMeansEstimator::~kMeansEstimator()
{
    if (created_list)
    {
        delete[] point_list;
    }
}