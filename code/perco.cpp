#include "perco.hpp"
#include "monte_carlo_integral.hpp"

int main(int argc, char** argv){
    const int t_end=stoi(argv[2]);
    const double R=4;
    const int L=50;
    const int N=2000;
    const int seeds = stoi(argv[1]);
    int t_perc, counter;
    double prop;
    Crandom ran64(1);
    //Percolacion perc(L,t_end,R);
    Percolacion *perc;
    Monte_Carlo_Integral *Area;
    //Monte_Carlo_Integral Area(L,R,N);

    std::ofstream areas("results/areas_"+to_string(L)+".dat");
    areas << "seed" <<"\t"<<"Area"<<std::endl;

    for(int s=0;s < seeds; s++){
        std::cout << "Semilla: "<< s <<"\r";
        ran64 = Crandom(s);
        counter = 0;
        perc = new Percolacion(L,t_end,R);
        Area = new Monte_Carlo_Integral(L,R,N);

        perc->create_system(ran64);
        t_perc=perc->t_percolante();
        //std::cout << "Cluster percolante en t=" <<t_perc <<std::endl;


        counter = Area->mci(perc->get_b(), t_perc);
        prop = double(counter)/double(N);

        // std::cout << "phi_eff=" << prop << "\n"
        //           << "Area=" << prop*L*L << "\n";

        areas << s <<"\t" << prop*L*L <<std::endl;

        delete Area;
        delete perc;
    }

    //perc->print_system("results/results_"+to_string(L)+".dat", t_perc);
    //Area->print(perc->get_b(),t_perc,"results/mci_circles.dat","results/mci_points.dat");
    areas.close();

    return 0;
}
