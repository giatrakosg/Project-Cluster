//
//  Clustering.cpp
//  Project-Cluster
//
//  Created by <author> on 19/11/2019.
//
//

#include "Clustering.hpp"

Clustering::Clustering(Database *db,int num_of_clusters ,int init_f,int assign_f,int update_f) : db(db) , k(num_of_clusters){
    flags[0] = init_f ;
    flags[1] = assign_f ;
    flags[2] = update_f ;
    std::cout << "Started clustering with \n" <<
    "k=" << k << std::endl ;

}
void Clustering::random_init(void) {
    // We produce k distinct integers in the [0,n) range that
    // are the selected initial centers of the clusters

    std::uniform_int_distribution<int> distribution(0,db->getSize() - 1) ; // Uniform distribution used for
    // random select

    std::set<int> used ;
    int selected = 0 ;
    while (selected < k) {
        int index = distribution(this->generator);
        if (!(used.find(index) == used.end())) {
            continue ;
        }
        used.insert(index);
        // Add the the generated object to the representative map
        representative.insert(std::pair<int,int> (selected,index));
        selected++;
    }

}
void Clustering::kmeans_init(void) {}
void Clustering::lloyd_assign(void) {}
void Clustering::range_search_assign(void) {}
void Clustering::pam_update(void) {}
void Clustering::mean_update(void){}

void Clustering::init(void) {
    if (flags[0] == 0) {
        random_init();
    } else if (flags[0] == 1) {
        kmeans_init();
    }
}
void Clustering::assign(void) {
    if (flags[1] == 0) {
        lloyd_assign();
    } else if (flags[1] == 1) {
        range_search_assign();
    }
}
void Clustering::update(void) {
    if (flags[2] == 0) {
        pam_update();
    } else if (flags[2] == 1) {
        mean_update();
    }
}
void Clustering::runClustering(void) {
    init();
    /*
    for (size_t i = 0; i < MAX_ITERATIONS; i++) {
        assign();
        update();
    }
    */

}
void Clustering::printRepresentatives(void) {
    for (auto const& x : representative)
    {
        Item * x_it = db->getItem(x.second);
        std::cout << x.first  // string (key)
                  << ':'
                  << x_it->getId() // string's value
                  << std::endl ;
    }
}
Clustering::~Clustering() {}
