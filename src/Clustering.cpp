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
    distribution = new std::uniform_int_distribution<int> (0,db->getSize() - 1); // We produce number in the
}
void Clustering::random_init(void) {

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

Clustering::~Clustering() {}
