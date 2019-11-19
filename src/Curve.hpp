//
//  Curve.hpp
//  Project-Cluster
//
//  Created by <author> on 18/11/2019.
//
//

#ifndef Curve_hpp
#define Curve_hpp

#include <stdio.h>
#include "Item.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std ;

struct Point {
    double x ;
    double y ;
    Point(double x,double y) : x(x) , y(y) {}
};


class Curve : public Item {
private:
    std::vector<Point *> points;
public:
    Curve(std::string );
    friend ostream& operator<<(ostream& os, const Curve& v) {
    os << "[ " << v.id << "|" ;
    for (size_t i = 0; i < v.points.size(); i++) {
        os << "(" << v.points[i]->x << "," << v.points[i]->y << "),"  ;
    }
    os << "]\n" ;
    return os ;
    }
    bool isEqual(Item &q) ;
    void addPoint(double ,double );
    double distance(Item &q) {}

    ~Curve();
protected:

};


#endif /* Curve_hpp */
