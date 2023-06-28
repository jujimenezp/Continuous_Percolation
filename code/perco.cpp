#include "perco.hpp"
#include "monte_carlo_integral.hpp"


int main(int argc, char** argv){
    const int t_end=stoi(argv[2]);
    const double R=3;
    //const int L=135;
    int Ls[] = {45, 60, 75, 90, 120, 135};
    //int Ls[] = {120};
    const int Ns[] = {450*45, 600*60, 750*75, 900*90, 1200*120, 1350*135};
    const int seeds = stoi(argv[1]);
    int t_perc, counter;
    double prop;
    Crandom *ran64;
    //Percolacion perc(L,t_end,R);
    //Monte_Carlo_Integral Area(L,R,N);
    Percolacion3D *perc;
    Monte_Carlo_Integral3D *Volume;

    for (int i=0; i < sizeof(Ls)/sizeof(Ls[0]); i++){
        std::cout << "\nL=" << Ls[i] << '\n';

        std::ofstream volumes;
        volumes.open("results/volumes_"+to_string(Ls[i])+".dat", std::ios_base::app);
        volumes << "seed" <<"\t"<<"Volume"<<'\n';

        for(int s=0;s < seeds; s++){
            std::cout <<"\r" << "Semilla: "<< s <<std::flush;

            perc = new Percolacion3D(Ls[i],t_end,R);
            Volume = new Monte_Carlo_Integral3D(Ls[i],R,Ns[i]);
            ran64 = new Crandom(s);

            perc->create_system(*ran64);
            t_perc=perc->t_percolante();
            //std::cout << "Cluster percolante en t=" <<t_perc <<std::endl;


            counter = Volume->mci(perc->get_b(), t_perc);
            prop = double(counter)/double(Ns[i]);

            // std::cout << "phi_eff=" << prop << "\n"
            //           << "Area=" << prop*Ls[i]*Ls[i] << "\n";

            volumes << s <<"\t" << prop <<'\n';

            //perc->print_system("results/results_"+to_string(Ls[i])+".dat", t_perc);
            //Area->print(perc->get_b(),t_perc,"results/mci_circles.dat","results/mci_points.dat");

            delete ran64;
            delete Volume;
            delete perc;
        }

        volumes.close();
    }

    return 0;
}
