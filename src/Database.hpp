//
//  Database.hpp
//  Project-Cluster
//
//  Created by <author> on 18/11/2019.
//
//

#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include "Item.hpp"
#include <string>
#include <vector>

class Database {
private:
    std::vector<Item *> items;
public:
    Database();
    void printItem(std::string ); // Prints the item stored with that string id
    void addItem(Item *); // Adds item to database
    Item * getItem(std::string ); // Get a pointer to the Item stored by string
    int getSize(void) ; // Get size of database
    virtual int getDimension(void) ; // Gets the dimension of the data stored (for vectors = dimension of R , for curves = number of points)
    ~Database();
protected:

};


#endif /* Database_hpp */
