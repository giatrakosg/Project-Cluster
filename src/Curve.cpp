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
Curve::~Curve() {
    for (size_t i = 0; i < points.size(); i++) {
        delete points[i] ;
    }
}
