#include "perco.hpp"

int main(int argc, char** argv){
    const int t_end=stoi(argv[2]);
    const double R=3;
    const int L=50;
    Crandom ran64(stoi(argv[1]));
    Percolacion perc(L,t_end,R);

    perc.create_system(ran64);
    perc.find_t_cluster();
    perc.print_system("results.dat");
    return 0;
}
