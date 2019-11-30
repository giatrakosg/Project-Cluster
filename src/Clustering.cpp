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
        for (int i = 0; i < db->getSize(); i++) {
            for (int j = 0; j < db->getSize(); j++) {
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
        Item *m = db->getItem(index)->clone();
        //m->deepCopy(db->getItem(index));
        // Add the the generated object to the representative map
        representative.insert(std::pair<int,Item *> (selected,m));
        selected++;
        // In case of medoid representation we store the index of the selected
        if (flags[2] == 0) {
            medoid_repr[selected] = index ;
        }
    }

}
Curve * Clustering::init_dba(std::vector<Curve *> &Sn) {
    double mean_length = 0 ;
    int num_curves = Sn.size() ;
    // Empty cluster
    if (num_curves == 0) {
        return NULL ;
    }
    for (size_t i = 0; i < Sn.size(); i++) {
        mean_length += Sn[i]->getSize() / (double) num_curves ;
    }
    // We count the number of curves with length greater that the mean
    int num_gt_mean = std::count_if(Sn.begin(),Sn.end(),
    [mean_length](Curve *c) {
        return c->getSize() >= mean_length;
    });
    // Sort the vector of Curves by descending order
    std::sort(Sn.begin(),Sn.end(),
    [] (Curve *a,Curve *b) {
        return a->getSize() > b->getSize() ;
    });
    // We produce the index of the randomly selected curve
    std::uniform_int_distribution<int> dis(0,num_gt_mean-1);
    int rind = dis(generator);
    Curve * s0 = Sn[rind]->random_subsequence(mean_length);
    return s0 ;
    // We have selected a random sequence whose length is greater or equal to the mean length of all curves
    // Now we must create a random subsequence of s0 with length = mean_length

}
Point * Clustering::meanPoint(std::vector<Point *> m) {
    double sumx = 0;
    double sumy = 0;
    int n = m.size();
    for (size_t i = 0; i < m.size(); i++) {
        sumx += m[i]->x;
        sumy += m[i]->y;
    }
    Point *k = new Point(sumx/n,sumy/n);
    return k ;
}
Curve * Clustering::dba(std::vector<Curve *> Sn) {
    Curve *C = init_dba(Sn);
    if (C == NULL) {
        return NULL ;
    }
    int lambda = C->getSize();
    int iterations = MAX_MEAN_ITER ;
    while (iterations>0) {
        Curve *C_prime = new Curve(C->getId()) ;
        for (int i = 0; i < C->getSize(); i++) {
            Point *m = C->getPoint(i);
            C_prime->addPoint(m->x,m->y);
        }
        std::vector<std::vector<Point *>> A;
        for (int i = 0; i < lambda; i++) {
            A.push_back(std::vector<Point *>());
        }

        for (size_t i = 0; i < Sn.size(); i++) {
            auto lpairs = C->dtwBestTraversal(Sn[i]);
            for (auto &p : lpairs) {
                /*
                if (p.second >= Sn[i]->getSize()) {
                    printf("Error\n");
                }
                */
                A[p.second].push_back(Sn[i]->getPoint(p.first));
            }
        }
        C->clear();
        //Curve *C2 = new Curve("c2") ;
        for (size_t i = 0; i < A.size(); i++) {
            Point * np = meanPoint(A[i]);
            C->addPoint(np->x,np->y);
        }
        //C->clear();
        //C = C2 ;
        if (C->isEqual(C_prime)) {
            delete C_prime ;
            break ;
        }
        delete C_prime ;
        iterations--;
    }
    return C ;
}

double Clustering::D(Item *t){
    double min_distance = t->distance(representative[0]); //vazw ws minimum distance enos Item tin apostasi apo to prwto centroid pou 
    for (size_t i = 1; i < representative.size(); i++){ //vrisketai sta representatives
        double dist = t->distance(representative[i]);
        if (dist < min_distance){
            min_distance = dist;
        }
    }
    return min_distance;
}

int Clustering::find_new_centroid(set<int> &used){
    vector< std::pair<int,double> > partial_sum_array; //pinakas tetragwnwn merikwn a8roismatwn
    partial_sum_array.push_back(std::pair<int,double> (-1,0.0)) ; //vazw ws prwto item sto pinaka to -1,0 giati o ari8mos -1
    double min_distance; //den anikei sto set mas kai i apostasi 0.0 gia na arxikopoiisoume to a8roisma twn merikwn apostasewn
    double min_dif = pow(D(db->getItem(0)),2); //vazw ws min difference ti minimum apostasi tou 1ou Item sti vasi apo to centroid tou
    //uparxei periptwsi to Item 0 na einai centroid
    for (size_t i = 0; i < db->getSize(); i++){ //ftiaxnei to pinaka twn tetragwnwn twn merikwn a8roismatwn
        if (!(used.find(i) == used.end())){ //an to Item einai sta used diladi einai centroid tote de vriskei tin minimum apostasi tou
            continue;
        }
        min_distance = pow(D(db->getItem(i)),2) ; //vriskw tin minimum distance enos simeiou apo to centroid tou kai tin apo8ikeuw 
        std::pair<int,double> p = partial_sum_array[partial_sum_array.size() - 1] ; //ftiaxnw ena kainourio pair p wste na krataw ti
        //meriki apostasi tou proigoumenou Item tou pinaka pou mou xreiazetai gia to Item pou exw
        partial_sum_array.push_back(std::pair<int,double> (i,p.second + min_distance)) ; //pros8etw ti metriki apostasi tou proigoumenou 
        //item me tou trexontos wste na ftia3w ti meriki apostasi tou trexontos item
        if (min_dif > min_distance) //to  min dif einai i mikroteri metriki apostasi tou pinaka 
            min_dif = min_distance ; //kai ti xrisimopoiw gia to binary search

    } 
    std::uniform_int_distribution<int> distribution(0,partial_sum_array[partial_sum_array.size() - 1].second) ; 
    double x = distribution(this-> generator) ; //pairnw ena random ari8mo anamesa sto 0 kai ti megisti metriki apostasi
    //pou einai i metriki apostasi tou item tou teleutaiou antikeimenou tou pinaka partial_sum_arrat
    int new_centroid_position = Binary_search(partial_sum_array,x,min_dif,partial_sum_array[1].second,partial_sum_array[partial_sum_array.size() - 1].second);
    //kanw binary search gia na vrw ti 8esi tou kainouriou item
    return new_centroid_position ;
}

//epistrefei ti 8esi tou neou centroid sto db
int Clustering::Binary_search(vector< std::pair<int,double> > &partial_sum_array,double x,double min_dif,int l,int r){ //to l einai to prwto kai to r einai to teleutaio stoixeio
    if (r >= 1){
        int mid = 1 + (r - 1) / 2;
        if (abs(x - partial_sum_array[mid].second) <= min_dif)
            return partial_sum_array[mid].first;
        if (x - partial_sum_array[mid].second > min_dif)
            return Binary_search(partial_sum_array,x,min_dif,l,mid - 1);
        return Binary_search(partial_sum_array,x,min_dif,mid + 1,r);
    }
}


void Clustering::kmeans_init(void) {
    std::uniform_int_distribution<int> distribution(0,db->getSize() - 1) ; // Uniform distribution used for

    int index = distribution(this -> generator); //to index einai i 8esi pou exei to item sti vasi
    int selected = 0;
    std::set<int> used ;
    used.insert(index) ;
    Item *m = db->getItem(index);
    representative.insert(std::pair<int,Item *> (selected,m));
    selected++ ;
    while (selected < k){
        index = find_new_centroid(used) ;
        used.insert(index) ;
        m = db->getItem(index) ;
        representative.insert(std::pair<int,Item *> (selected,m)) ;
        selected++ ; 
    }

}

void Clustering::lloyd_assign(void) {
    // Clear out previous assignments
    for (auto & x : assigned)
    {
        x.second.clear();
    }

    for (int i = 0; i < db->getSize(); i++) {
        double min_dist = INFINITY ;
        int min_index = -1 ;
        for (int j = 0; j < k; j++) {
            if (representative[j] == NULL) {
                continue ;
            }
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
void Clustering::mean_update(void){
    if (isCurve) {
        for (auto &cluster : assigned) {
            std::vector<Curve *> curves;
            for (size_t i = 0; i < cluster.second.size(); i++) {
                curves.push_back(dynamic_cast<Curve *> (db->getItem(cluster.second.at(i)))) ;
            }
            auto nm = dba(curves);
            delete representative[cluster.first] ;
            representative[cluster.first] = nm ;
        }
    }
}

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
        std::cout << x.first << ':' ;
        if (x.second == NULL) {
            std::cout << "Empty cluster" << std::endl ;
            continue ;
        }
        std::cout << x.second->getId() << std::endl ;
    }
}
Clustering::~Clustering() {
    if (flags[2] == 0) {
        /* code */
    }
    if (flags[2] == 1) {
        // We delete the represenentatives if mean update since they do not belong to the db an wont be deleted
        // Else , since the representatives are in the dataset they will be deleted by the db
        for(auto &p : representative) {
            delete p.second ;
        }
    }
}
