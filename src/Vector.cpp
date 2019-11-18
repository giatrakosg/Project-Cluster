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
Vector::~Vector() {}
