#include "monte_carlo_integral.hpp"

int main(int argc, char** argv){
    int SEED=std::stoi(argv[1]), t_end=std::stoi(argv[2]), N=std::stoi(argv[3]);

    // Generate (x,y) circles coordinates
    std::vector<double> b;
    generate(b, t_end, SEED);
    // Monte-Carlo
    std::vector<double> samples;
    int counter = monte_carlo_integral(b, t_end, samples, N);
    double phi_eff = double(counter)/double(N);
    // Print
    print(b, samples, t_end, N);
    std::cout << "counter/N = " << counter << "/" << N << " = " << phi_eff << std::endl;
    std::cout << "Area = " << phi_eff*L*L << std::endl;

    return 0;
}
