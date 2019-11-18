//
//  Vector.cpp
//  Project-Cluster
//
//  Created by <author> on 18/11/2019.
//
//

#include "Vector.hpp"

Vector::Vector(std::string id,std::vector<double> coordinates) : Item(id) , coordinates(coordinates) {
}
bool Vector::isEqual(Item &q ) {
    Vector &p = dynamic_cast<Vector &> (q) ;
    bool idcmp = p.getId() == this->id ;
    // TODO implement point for point comparison
    return idcmp ;
}
Vector::~Vector() {}
