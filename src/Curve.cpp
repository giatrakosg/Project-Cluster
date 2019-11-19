//
//  Curve.cpp
//  Project-Cluster
//
//  Created by <author> on 18/11/2019.
//
//

#include "Curve.hpp"

Curve::Curve(std::string id) : Item(id)  {}
bool Curve::isEqual(Item &q ) {
    Curve &p = dynamic_cast<Curve &> (q) ;
    bool idcmp = p.getId() == this->id ;
    // TODO implement point for point comparison
    return idcmp ;
}
void Curve::addPoint(double px,double py) {
    Point *p = new Point(px,py);
    points.push_back(p);
}
int Curve::getSize() {
    return points.size();
}
Point * Curve::getPoint(int i) {
    return points[i] ;
}
double min3(double x ,double y , double z) {
    if (x < y) {
        if (x < z) {
            return x ;
        } else {
            return z ;
        }
    } else if (y < z){
        return y ;
    }
}

double Curve::distance(Item *p) {
    Curve *q = dynamic_cast<Curve *> (p) ;
    int n = this->getSize();
    int m = q->getSize() ;
    double DTW[n+1][m+1] ; // Array with distances
    for (size_t i = 0; i < n+1; i++) {
        for (size_t j = 0; j < m+1; j++) {
            DTW[i][j] = INFINITY ;
        }
    }
    DTW[0][0] = 0 ;
    for (size_t i = 1; i < n+1; i++) {
        for (size_t j = 1; j < m+1; j++) {
            double cost = (q->getPoint(j-1))->dist((points[i-1]));
            DTW[i][j] = cost + min3(DTW[i-1][j],DTW[i][j-1],DTW[i-1][j-1]);
        }
    }
    return DTW[n][m];

}
Curve::~Curve() {
    for (size_t i = 0; i < points.size(); i++) {
        delete points[i] ;
    }
}
