//
//  Parser.hpp
//  Project-Cluster
//
//  Created by <author> on 18/11/2019.
//
//

#ifndef Parser_hpp
#define Parser_hpp

#include "Database.hpp"
#include <stdio.h>
#include <string>
// Pure virtual class that describes an interface


class Parser {
private:
    Database *db ; // Database class that the data is stored to
public:
    Parser(Database *);
    virtual void parseFile(std::string &) = 0 ; // Parses the given file
    ~Parser();
protected:

};


#endif /* Parser_hpp */
