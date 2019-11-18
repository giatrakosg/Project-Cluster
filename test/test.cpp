#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/Vector.hpp"
#include "../src/Database.hpp"
#include "../src/Item.hpp"
#include "../src/Parser.hpp"
#include "../src/ConfParser.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <utility>

TEST_CASE( "storing vectors" ) {
    std::vector<double> p1 {1.0,2.3,5.9} ;
    std::vector<double> p2 {1.3,2.3,2.2,3.1};
    std::vector<double> p3 {0,0};
    Vector v1 ("p1",p1);
    Vector v2 ("p2",p2);
    Vector v3 ("p3",p3);
    std::cout << v1 << " " << v2 << " " << v3 << std::endl ;

    Database db ;
    db.addItem(&v1);
    db.addItem(&v2);
    db.addItem(&v3);
    REQUIRE(db.getSize() == 3) ;
    REQUIRE(db.getItem("p1")->isEqual(v1));

}
TEST_CASE ("parsing vector data" ) {
    Database db ;
    Parser parser(&db);
    std::string input_file ("./data/test_vector_small_id.dat");
    parser.parseFile(input_file);
    std::vector<double> p1 {1.0,2.3,5.9} ;
    Vector v1 ("p1",p1);
    REQUIRE(db.getSize() == 3) ;
    REQUIRE(db.getItem("p1")->isEqual(v1));

}
TEST_CASE ("parsing curve data") {
    /*
    6	8	(-6.2582100000000001, 53.347799999999999) (-6.4272499999999999, 53.290799999999997) (-6.4272499999999999, 53.290799999999997) (-6.4272900000000002, 53.290799999999997) (-6.4272900000000002, 53.290799999999997) (-6.4271799999999999, 53.291400000000003) (-6.4265499999999998, 53.290100000000002) (-6.4272099999999996, 53.2911)
    */
    Database db ;
    Parser parser(&db);
    std::string input_file ("./data/trajectories_dataset_smaller.dat");
    parser.parseFile(input_file);
    std::vector<std::pair<double,double>> points ;

    Curve c1 ("6");
    for (size_t i = 0; i < points.size(); i++) {
        c1.addPoint(points[i].first,points[i].second);
    }
    REQUIRE(db.getSize() == 100) ;
    REQUIRE(db.getItem("6")->isEqual(c1));
}
TEST_CASE ("parsing config file") {
    std::string config_file ("./data/test_cluster.conf");
    int a , b , c , d ;
    ConfParser parser(config_file) ;
    parser.parseConfig(a,b,c,d);
    REQUIRE(a == 5) ;
    REQUIRE(b == 10) ;
    REQUIRE(c == 2) ;
    REQUIRE(d == 3) ;
}
