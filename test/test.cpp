#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/Vector.hpp"
#include "../src/Database.hpp"
#include "../src/Item.hpp"
#include "../src/Parser.hpp"
#include "../src/ConfParser.hpp"
#include "../src/Clustering.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <utility>

TEST_CASE( "storing vectors" ) {
    std::vector<double> p1 {1.0,2.3,5.9} ;
    std::vector<double> p2 {1.3,2.3,2.2,3.1};
    std::vector<double> p3 {0,0};
    Vector *v1 = new Vector ("p1",p1);
    Vector *v2 = new Vector ("p2",p2);
    Vector *v3 = new Vector ("p3",p3);
    std::cout << v1 << " " << v2 << " " << v3 << std::endl ;

    Database db ;
    db.addItem(v1);
    db.addItem(v2);
    db.addItem(v3);
    REQUIRE(db.getSize() == 3) ;
    REQUIRE(db.getItem("p1")->isEqual(*v1));

}
TEST_CASE ("parsing vector data" ) {
    Database db ;
    Parser parser(&db);
    std::string input_file ("./data/test_vector_small_id.dat");
    parser.parseFile(input_file);
    std::vector<double> p1 {1.0,2.3,5.9} ;
    Vector v1 ("p1",p1);
    REQUIRE(db.getSize() == 14) ;
    REQUIRE(db.getItem("p1")->isEqual(v1));

}
TEST_CASE ("parsing curve data") {
    /*
    6	8	(-6.2582100000000001, 53.347799999999999) (-6.4272499999999999, 53.290799999999997) (-6.4272499999999999, 53.290799999999997) (-6.4272900000000002, 53.290799999999997) (-6.4272900000000002, 53.290799999999997) (-6.4271799999999999, 53.291400000000003) (-6.4265499999999998, 53.290100000000002) (-6.4272099999999996, 53.2911)
    */
    Database db ;
    Parser parser(&db);
    std::string input_file ("../data/curves_clustering/input_projection6.csv");
    parser.parseFile(input_file);
    std::vector<std::pair<double,double>> points ;

    Curve *c1 ;
    c1 = dynamic_cast<Curve *>(db.getItem("4474"));

    REQUIRE(db.getSize() == 1600) ;
    REQUIRE(c1 != NULL);
    //REQUIRE(db.getItem("6")->isEqual(c1));
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
TEST_CASE ("Item distance") {
    std::vector<double> p1 {1.0,2.3,6.9} ;
    std::vector<double> p2 {1.5,2.3,2.9};
    Vector v1 ("p1",p1);
    Vector v2 ("p2",p2);
    double dis = v1.distance(&v2);
    REQUIRE(dis == 4.5);

    Curve c1 ("c1");
    c1.addPoint(1,0);
    c1.addPoint(1,0);
    c1.addPoint(2,0);
    c1.addPoint(3,0);
    c1.addPoint(2,0);
    c1.addPoint(0,0);


    Curve c2 ("c2");
    c2.addPoint(0,0);
    c2.addPoint(1,0);
    c2.addPoint(1,0);
    c2.addPoint(2,0);
    c2.addPoint(3,0);
    c2.addPoint(1,0);
    c2.addPoint(1,0);


    Curve c3 ("c3");
    c3.addPoint(0,1);
    c3.addPoint(1,0);
    Curve c4 ("c4");
    c4.addPoint(0,1);
    c4.addPoint(1,0);

    REQUIRE(c1.distance(&c2) == 3);
    REQUIRE(c3.distance(&c4) == 0);



}
TEST_CASE("Clustering initialization") {
    Database db ;
    Parser parser(&db);
    std::string input_file ("../data/Ex2_Datasets/DataVectors_5_500x100.csv");
    parser.parseFile(input_file);
    Clustering cluster (&db,false,5,0,0,0) ;
    cluster.runClustering();
    cluster.printRepresentatives();
}
TEST_CASE("DTW_BEST_TRAVERSAL") {
    Curve c1 ("c1");
    c1.addPoint(1,0);
    c1.addPoint(1,0);
    c1.addPoint(2,0);
    c1.addPoint(3,0);
    c1.addPoint(2,0);
    c1.addPoint(0,0);


    Curve c2 ("c2");
    c2.addPoint(0,0);
    c2.addPoint(1,0);
    c2.addPoint(1,0);
    c2.addPoint(2,0);
    c2.addPoint(3,0);
    c2.addPoint(1,0);
    c2.addPoint(1,0);
    auto x = c1.dtwBestTraversal(&c2);
    std::vector<pair<int,int>> outp;
    outp.push_back(std::pair<int,int>(5,4));
    outp.push_back(std::pair<int,int>(4,3));
    outp.push_back(std::pair<int,int>(3,2));
    outp.push_back(std::pair<int,int>(3,1));
    outp.push_back(std::pair<int,int>(2,1));
    outp.push_back(std::pair<int,int>(1,1));
    outp.push_back(std::pair<int,int>(0,0));
    REQUIRE(x == outp);
}

TEST_CASE("DBA") {
    Database *db = new Database();
    Parser parser(db);
    std::string input_file ("../data/curves_clustering/input_projection6.csv");
    parser.parseFile(input_file);
    Clustering cluster (db,true,5,0,0,1) ;
    std::vector<Curve *> curves;
    long curve_size_sum = 0 ;
    for (size_t i = 0; i < db->getSize(); i++) {
        Curve *m = dynamic_cast<Curve *> (db->getItem(i)) ;
        curves.push_back(m);
        curve_size_sum += m->getSize();
    }
    int mean_len = curve_size_sum / db->getSize();
    //Curve *c = cluster.init_dba(curves);
    //REQUIRE(c->getSize() == mean_len);
    cluster.runClustering();
    cluster.printRepresentatives();
    delete db ;
}
