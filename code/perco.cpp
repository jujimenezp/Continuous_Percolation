#include "perco.hpp"
#include "monte_carlo_integral.hpp"

int main(int argc, char** argv){
    const int t_end=stoi(argv[2]);
    const double R=3;
    //const int L=135;
    int Ls[] = {45, 60, 75, 90, 120, 135};
    //int Ls[] = {120};
    const int Ns[] = {1800, 2000, 5000, 6000, 1000, 18000};
    const int seeds = stoi(argv[1]);
    int t_perc, counter;
    double prop;
    Crandom *ran64;
    //Percolacion perc(L,t_end,R);
    Percolacion *perc;
    Monte_Carlo_Integral *Area;
    //Monte_Carlo_Integral Area(L,R,N);

    for (int i=0; i < sizeof(Ls)/sizeof(Ls[0]); i++){
        std::cout << "L=" << Ls[i] << std::endl;

        std::ofstream areas("results/areas_"+to_string(Ls[i])+".dat");
        areas << "seed" <<"\t"<<"Area"<<std::endl;
        for(int s=0;s < seeds; s++){
            std::cout << "Semilla: "<< s <<"\r";

            perc = new Percolacion(Ls[i],t_end,R);
            Area = new Monte_Carlo_Integral(Ls[i],R,Ns[i]);
            ran64 = new Crandom(s);

            perc->create_system(*ran64);
            t_perc=perc->t_percolante();
            //std::cout << "Cluster percolante en t=" <<t_perc <<std::endl;


            counter = Area->mci(perc->get_b(), t_perc);
            prop = double(counter)/double(Ns[i]);

            // std::cout << "phi_eff=" << prop << "\n"
            //           << "Area=" << prop*Ls[i]*Ls[i] << "\n";

            areas << s <<"\t" << prop*Ls[i]*Ls[i] <<std::endl;

            //perc->print_system("results/results_"+to_string(Ls[i])+".dat", t_perc);
            Area->print(perc->get_b(),t_perc,"results/mci_circles.dat","results/mci_points.dat");

            delete ran64;
            delete Area;
            delete perc;
        }

        areas.close();
    }

    return 0;
}
