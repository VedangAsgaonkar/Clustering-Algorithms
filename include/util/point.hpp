#ifndef _POINT_H_
#define _POINT_H_

#include<string>
#include<iostream>
#include<cmath>

/**
 * @brief Implements a basic point in two dimensions
 * 
 */
class point{
public:
    double x;
    double y;
    std::string label;
    point();
    point(double x, double y);
    point(double x, double y, std::string label);
};

inline std::istream& operator>>(std::istream &is, point &p){
    is >> p.x >> p.y;
    p.label = "";
    return is;
}

inline std::ostream& operator<<(std::ostream &os, point &p){
    os << p.label << " ( " << p.x << ", " << p.y << " ) ";
    return os;
}

inline double distance(point& p1, point& p2){
    return std::sqrt( (p1.x-p2.x)*(p1.x-p2.x) +  (p1.y-p2.y)*(p1.y-p2.y) ) ;
}
inline double distance(point *p1, point *p2){
    return std::sqrt( (p1->x-p2->x)*(p1->x-p2->x) +  (p1->y-p2->y)*(p1->y-p2->y) ) ;
}

#endif