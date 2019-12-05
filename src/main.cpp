#include "CMDParser.hpp"
#include "ConfParser.hpp"
#include <string>
#include <iostream>
#include <unistd.h>
#include <thread>


struct cluster_t_args {
    cluster_t_args(){}
    bool isCurve ;
    int k ;
    unsigned int flags[3];
    //std::ostream & out ;
};

void cluster_thread_f(cluster_t_args args) {
    //cluster_t_args * args = ( *) _args ;
    std::cout << args.isCurve << " " << args.k << " " << args.flags[0] << args.flags[1] << args.flags[2] << std::endl ;
}

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

        args.isCurve = false ;
        args.k = nclusters ;
        //args->out = std::cout ;
        std::thread t(cluster_thread_f,args);
        t.join();
    }
    return 0;
}
