//
//  Database.cpp
//  Project-Cluster
//
//  Created by <author> on 18/11/2019.
//
//

#include "Database.hpp"

Database::Database()  {}
void Database::addItem(Item *t) {
    items.push_back(t);
}
Item * Database::getItem(std::string qid) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i]->getId() == qid) {
            return items[i];
        }
    }
    return NULL ;
}
int Database::getSize(void) {
    return items.size();
}
int Database::getDimension(void) {}

Database::~Database() {}
