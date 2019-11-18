//
//  VectorParser.hpp
//  Project-Cluster
//
//  Created by <author> on 18/11/2019.
//
//

#ifndef VectorParser_hpp
#define VectorParser_hpp

#include <stdio.h>
#include <string>
#include "Parser.hpp"

class VectorParser : Parser{
private:
public:
    VectorParser(Database *);
    void parseFile(std::string &);
    ~VectorParser();
protected:

};


#endif /* VectorParser_hpp */
