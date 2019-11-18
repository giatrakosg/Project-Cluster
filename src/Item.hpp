//
//  Item.hpp
//  Project-Cluster
//
//  Created by <author> on 18/11/2019.
//
//

#ifndef Item_hpp
#define Item_hpp

#include <stdio.h>
#include <string>
#include <iostream>

// Virtual function that represents items stored in the database

class Item {
private:
public:
    Item(std::string );
    ~Item();
protected:
    std::string id ; // Item id
};


#endif /* Item_hpp */
