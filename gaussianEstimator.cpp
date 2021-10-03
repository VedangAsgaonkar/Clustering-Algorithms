#include "gaussianEstimator.h"
#include <cmath>

gaussianEstimator::gaussianEstimator(point *point_list, int n)
{
    vec_list = new vec2[n];
    for (int i = 0; i < n; i++)
    {
        vec_list[i].e[0] = point_list[i].x;
        vec_list[i].e[1] = point_list[i].y;
    }
    this->n = n;
}

gaussianEstimator::gaussianEstimator(double *xlist, double *ylist, int n)
{
    vec_list = new vec2[n];
    for (int i = 0; i < n; i++)
    {
        vec_list[i].e[0] = xlist[i];
        vec_list[i].e[1] = ylist[i];
    }
    this->n = n;
}

double gaussianEstimator::gaussianProbability(const vec2 &point, const vec2 &mean, const matrix2 &cov) const
{
    double power = dot((point - mean), cov.inverse() * (point - mean));
    double det = cov.determinant();
    return exp(-power / 2) / (det * sqrt(6.28));
}

std::multimap<int, int> gaussianEstimator::cluster(int k, int iter) const
{
    // initialization
    matrix2 covariances[k];
    vec2 means[k];
    double max_x = vec_list[0].e[0];
    double min_x = vec_list[0].e[0];
    double max_y = vec_list[0].e[1];
    double min_y = vec_list[0].e[1];
    for (int i = 1; i < n; i++)
    {
        if (max_x < vec_list[i].e[0])
        {
            max_x = vec_list[i].e[0];
        }
        if (max_y < vec_list[i].e[1])
        {
            max_y = vec_list[i].e[1];
        }
        if (min_x > vec_list[i].e[0])
        {
            min_x = vec_list[i].e[0];
        }
        if (min_y > vec_list[i].e[1])
        {
            min_y = vec_list[i].e[1];
        }
    }
    for (int i = 0; i < k; i++)
    {
        double a, b, c;
        do
        {
            a = std::min(min_x, min_y) + std::min(max_x - min_x, max_y - min_y) * drand48();
            b = std::min(min_x, min_y) + std::min(max_x - min_x, max_y - min_y) * drand48();
            c = std::min(min_x, min_y) + std::min(max_x - min_x, max_y - min_y) * drand48();
        } while (a * b > 0.0001 + c * c);
        covariances[i].a[0][0] = a;
        covariances[i].a[1][1] = b;
        covariances[i].a[1][0] = c;
        covariances[i].a[0][1] = c;

        means[i].e[0] = min_x + (max_x - min_x) * drand48();
        means[i].e[1] = min_y + (max_y - min_y) * drand48();
    }

    std::multimap<int, int> clusters;

    //iterations
    for (int run = 0; run < iter; run++)
    {
        // for (int i = 0; i < k; i++)
        // {
        //     std::cout << means[i] << std::endl;
        // }

        clusters.erase(clusters.begin(), clusters.end());
        for (int i = 0; i < n; i++)
        {
            int index = 0;
            double max_prob = gaussianProbability(vec_list[i], means[0], covariances[0]);
            for (int j = 1; j < k; j++)
            {
                if (gaussianProbability(vec_list[i], means[j], covariances[j]) > max_prob)
                {
                    index = j;
                    max_prob = gaussianProbability(vec_list[i], means[j], covariances[j]);
                }
            }
            clusters.insert(std::pair<int, int>(index, i));
        }

        int previous_cluster = -1;
        vec2 sum(0, 0);
        matrix2 sum2(0, 0, 0, 0);
        int cnt = 0;
        for (auto it = clusters.begin(); it != clusters.end(); it++)
        {
            if (it->first == previous_cluster)
            {
                sum = sum + vec_list[it->second];
                sum2 = sum2 + outer_product(vec_list[it->second], vec_list[it->second]);
                cnt++;
            }
            else
            {
                if (previous_cluster != -1)
                {
                    if (cnt != 0)
                    {
                        means[previous_cluster] = sum / cnt;
                        covariances[previous_cluster] = (sum2 / cnt) - outer_product(means[previous_cluster], means[previous_cluster]);
                    }
                }
                sum.e[0] = 0;
                sum.e[1] = 0;
                sum2.a[0][0] = 0;
                sum2.a[0][1] = 0;
                sum2.a[1][0] = 0;
                sum2.a[1][1] = 0;
                cnt = 0;
            }
        }
        if (cnt != 0)
        {
            means[previous_cluster] = sum / cnt;
            covariances[previous_cluster] = (sum2 / cnt) - outer_product(means[previous_cluster], means[previous_cluster]);
        }
    }

    return clusters;
}

gaussianEstimator::~gaussianEstimator()
{
    delete[] vec_list;
}