//
//  Clustering.cpp
//  Project-Cluster
//
//  Created by <author> on 19/11/2019.
//
//

#include "Clustering.hpp"

Clustering::Clustering(Database *db,bool isCurve , int num_of_clusters ,int init_f,int assign_f,int update_f) : db(db) , k(num_of_clusters) , isCurve(isCurve){
    flags[0] = init_f ;
    flags[1] = assign_f ;
    flags[2] = update_f ;
    std::cout << "Started clustering with \n" <<
    "k=" << k << std::endl ;
    if (flags[2] == 0) {
        std::cout << "Calculating pairwise distances...." ;
        for (size_t i = 0; i < db->getSize(); i++) {
            for (size_t j = 0; j < db->getSize(); j++) {
                double d = db->getItem(i)->distance(db->getItem(j));
                dist[std::pair<int,int> (i,j)] = d ;
            }
        }
        std::cout << "done" << std::endl ;

    }
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
        Item *m = db->getItem(index);
        // Add the the generated object to the representative map
        representative.insert(std::pair<int,Item *> (selected,m));
        selected++;
        // In case of medoid representation we store the index of the selected
        if (flags[2] == 0) {
            medoid_repr[selected] = index ;
        }
    }

}
void Clustering::kmeans_init(void) {}
void Clustering::lloyd_assign(void) {
    // Clear out previous assignments
    for (auto & x : assigned)
    {
        x.second.clear();
    }

    for (size_t i = 0; i < db->getSize(); i++) {
        double min_dist = INFINITY ;
        int min_index = -1 ;
        for (size_t j = 0; j < k; j++) {
            double d_to_c = db->getItem(i)->distance(representative[j]);
            if (d_to_c < min_dist) {
                min_index = j ;
                min_dist = d_to_c ;
            }
        }
        assigned[min_index].push_back(i) ;
    }
}
void Clustering::range_search_assign(void) {}
void Clustering::pam_update(void) {
    // We iterate through each cluster and update the medoid
    for (auto & x : assigned)
    {
        std::vector<int> &items = x.second ;
        double min_total_dist = INFINITY ;
        int min_index = -1 ;
        for (size_t i = 0; i < items.size(); i++) {
            double total_dist = 0 ;
            int index1 = items[i];
            for (size_t j = 0; j < items.size(); j++) {
                int index2 = items[j] ;
                total_dist += dist[pair<int,int>(index1,index2)] ; // We have already calculated the pairwise distances
            }
            if (total_dist < min_total_dist) {
                min_total_dist = total_dist ;
                min_index = index1 ;
            }
        }
        representative[x.first] = db->getItem(min_index);
        medoid_repr[x.first] = min_index ;
    }

}
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
    for (size_t i = 0; i < MAX_ITERATIONS; i++) {
        assign();
        update();
    }


}
void Clustering::printRepresentatives(void) {
    for (auto const& x : representative)
    {
        //Item * x_it = x.second;
        std::cout << x.first  // string (key)
                  << ':'
                  << x.second->getId() // string's value
                  << std::endl ;
    }
}
Clustering::~Clustering() {}
