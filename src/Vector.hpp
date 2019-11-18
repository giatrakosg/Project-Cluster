//
//  Vector.hpp
//  Project-Cluster
//
//  Created by <author> on 18/11/2019.
//
//

#ifndef Vector_hpp
#define Vector_hpp

#include <stdio.h>
#include "Item.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std ;

class Vector : public Item {
private:
    std::vector<double> coordinates ;
public:
    Vector(std::string ,std::vector<double>);
    friend ostream& operator<<(ostream& os, const Vector& v) {
    os << "[ " << v.id << "|" ;
    for (size_t i = 0; i < v.coordinates.size(); i++) {
        os << v.coordinates[i]<< ","  ;
    }
    os << "]\n" ;
    return os ;
    }
    bool isEqual(Item &q) ;


    ~Vector();
protected:

};


#endif /* Vector_hpp */
