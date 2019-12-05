#include "CMDParser.hpp"
#include "ConfParser.hpp"
#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include "Database.hpp"
#include "Parser.hpp"
#include "Clustering.hpp"

struct cluster_t_args {
    cluster_t_args(){}
    bool isCurve ;
    int k ;
    unsigned int flags[3];
    std::string input ;
    std::string out ;
    Database *db ;
    //std::ostream & out ;
};
/*
void cluster_thread_f(cluster_t_args args) {
    sleep(5);
    //cluster_t_args * args = ( *) _args ;
    std::cout << args.isCurve << " " << args.k << " " << args.flags[0] << args.flags[1] << args.flags[2] << std::endl ;
    Clustering cluster (args.db,args.isCurve,args.k,args.flags[0],args.flags[1],args.flags[2]);
    cluster.runClustering();
    cluster.printRepresentatives();
}
*/
int main(int argc, char **argv) {
    CMDParser cmd_p ;
    std::string input ;
    std::string config ;
    std::string output ;
    cmd_p.getArgs(argc,argv,input,config,output);
    std::cout << input << " " << config << " " << output << "\n" ;

    ConfParser conf_p (config) ;
    int nclusters ;
    int ngrids ;
    int nvht ;
    int nvfs ;
    conf_p.parseConfig(nclusters,ngrids,nvht,nvfs);

    Database *db = new Database() ;
    Parser parser(db);
    bool isCurve = parser.parseFile(input);

    std::ofstream file ;
    file.open(output);

    //std::vector<std::thread *> threads;
    //std::thread * cluster_ts = new std::thread[8] ;
    for (unsigned int i = 0; i < 8; i++) {
        int err ;
        int mask1 = 1 << 0 ;
        int mask2 = 1 << 1 ;
        int mask3 = 1 << 2 ;

        struct cluster_t_args args ;
        args.flags[0] = (i & mask1) >> 0;
        args.flags[1] = (i & mask2) >> 1;
        args.flags[2] = (i & mask3) >> 2;
        if (args.flags[0] == 1) {
            continue ;
        }

        args.isCurve = isCurve ;
        args.k = nclusters ;

        args.input = input ;
        args.out = "out";
        args.db = db ;
        //args->out = std::cout ;
        //std::thread *t = new

        //std::thread(cluster_thread_f,args);
        //threads.push_back(t);
        //t->join();
        Clustering cluster (db,args.isCurve,args.k,args.flags[0],args.flags[1],args.flags[2]);
        cluster.runClustering();
        cluster.printRepresentatives();
        cluster.printResults(file);
    }
    //sleep(10);
    //for (size_t i = 0; i < threads.size(); i++) {
    //    threads[i]->join();
    //}
    file.close();
    delete db ;
    return 0;
}
