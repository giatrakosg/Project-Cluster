//
//  Clustering.hpp
//  Project-Cluster
//
//  Created by <author> on 19/11/2019.
//
//

#ifndef Clustering_hpp
#define Clustering_hpp

#include <stdio.h>
#include <map>
#include <utility>
#include <random>

#include "Database.hpp"

using namespace std ;

class Clustering {
private:
    void init() ; // Does the initialization of the k centers
    void assign(); // Does the assignment of the n vectors to their clusters
    void update(); // Does the update of the k centers
    void random_init(); // Random selection of K items
    void kmeans_init(); // K-means++ selectionof first K items
    void lloyd_assign(); // Lloyd assignment
    void range_search_assign(); // Assignment by Range search
    void pam_update(); // Update using PAM (lloyds)
    void mean_update(); // Update using mean vectors / curve

    Database *db ; // Database with points
    int flags[3] ; // Flags used to determine which algorithms are used
    // for init , assign and update given by user
    std::map<pair<string,string> , double> dist; // Map with distances of each pair
    // of items
    std::map<int, string> representative; // Map that matches each cluster to each
    // representative center
    std::map<string, int> assigned; // Map that matches each item to its cluster

    std::uniform_int_distribution<int> distribution ; // Uniform distribution used for
    // random select
    std::default_random_engine generator;

public:
    Clustering(Database *,int ,int ,int ); // Database with data points
    // Followed by sequence of [0,1,0] etc that selects the init , assign and update
    // algorithms respectively
    void runClustering(); // Function called by main
    ~Clustering();
protected:

};


#endif /* Clustering_hpp */
