#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/Vector.hpp"

#include <vector>
#include <iostream>
#include <string>

TEST_CASE( "storing vectors" ) {
    std::vector<double> p1 {1.0,2.3,5.9} ;
    std::vector<double> p2 {1.3,2.3,2.2,3.1};
    std::vector<double> p3 {0,0};
    Vector v1 ("p1",p1);
    Vector v2 ("p2",p2);
    Vector v3 ("p3",p3);
    std::cout << v1 << " " << v2 << " " << v3 << std::endl ;

}
