#include "perco.hpp"

int main(int argc, char** argv){
    const int t_end=stoi(argv[2]);
    const double R=4;
    const int L=50;
    int t_perc;
    Crandom ran64(stoi(argv[1]));
    Percolacion perc(L,t_end,R);

    perc.create_system(ran64);
    // perc.find_papas(t_end);
    // perc.merge(t_end);
    // perc.print_system("results.dat",t_end);
    // perc.reset_clusters();

    t_perc=perc.t_percolante();
    std::cout << "Cluster percolante en t=" <<t_perc <<std::endl;

    perc.reset_clusters();
    perc.find_papas(t_perc);
    perc.merge(t_perc);
    perc.print_system("hay.dat",t_perc);

    perc.reset_clusters();
    perc.find_papas(t_perc-1);
    perc.merge(t_perc-1);
    perc.print_system("no_hay.dat",t_perc-1);
    return 0;
}
