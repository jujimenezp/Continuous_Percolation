#include "perco.hpp"

int main(int argc, char** argv){
    const int t_end=stoi(argv[2]);
    const int R=3;
    const int L=50;
    const int L2=L*L;
    double x=0,y=0;
    Crandom ran64(stoi(argv[1]));

    std::ofstream file("results.dat");
    file << "x\t" << "y\t" << "R" << std::endl;
    for(int t=0; t < t_end; t++){
        x = L*ran64.r(); y= L*ran64.r();
        file << x <<"\t"<< y <<"\t"<<R <<std::endl;
    }
    file.close();
}
