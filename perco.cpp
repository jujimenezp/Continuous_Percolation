#include "perco.hpp"

int main(int argc, char** argv){
    const int t_end=stoi(argv[2]);
    const double R=3;
    const int L=50;
    const int L2=L*L;
    Crandom ran64(stoi(argv[1]));
    std::vector<double> b;

    b = create_system(ran64, L, t_end);
    print_system("results.dat", b);
    double x = find_t_cluster(b,t_end,R);
    return 0;
}
