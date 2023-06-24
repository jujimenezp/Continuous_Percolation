#include "perco.hpp"
#include "monte_carlo_integral.hpp"

int main(int argc, char** argv){
    const int t_end=stoi(argv[2]);
    const double R=4;
    const int L=50;
    const int N=2000;
    int t_perc;
    Crandom ran64(stoi(argv[1]));
    Percolacion perc(L,t_end,R);
    Monte_Carlo_Integral Area(L,R,N);

    perc.create_system(ran64);

    t_perc=perc.t_percolante();
    std::cout << "Cluster percolante en t=" <<t_perc <<std::endl;

    //perc.b_resize(t_perc);
    perc.print_system("results/results.dat", t_perc);

    int counter;
    counter = Area.mci(perc.get_b(),t_perc);
    std::cout << "phi_eff=" << double(counter)/double(N) << "\n"
              << "Area=" << double(counter*L*L)/double(N);
    Area.print(perc.get_b(),t_perc,"results/mci_circles.dat","results/mci_points.dat");

    // perc.reset_clusters();
    // perc.find_papas(t_perc);
    // perc.merge(t_perc);
    // perc.print_system("results/hay.dat",t_perc);

    // perc.reset_clusters();
    // perc.find_papas(t_perc-1);
    // perc.merge(t_perc-1);
    // perc.print_system("results/no_hay.dat",t_perc-1);
    return 0;
}
