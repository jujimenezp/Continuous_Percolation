#pragma once
#include "perco.hpp"
#include <gsl/gsl_qrng.h>

#ifndef MONTE_CARLO_INTEGRAL_H_
#define MONTE_CARLO_INTEGRAL_H_

class Monte_Carlo_Integral{
    private:
        const int L, L2;
        const double R,D, N;
        std::vector<double> samples;
    public:
        Monte_Carlo_Integral(const int Li, const double Ri, const int Ni) :
            L(Li), L2(L*L), R(Ri), D(2*Ri), N(Ni){}
        int mci(std::vector<double> b, const int t_end);
        void print(std::vector<double> b, const int t_end, std::string circles_file, std::string samples_file);
        void reset_samples(){samples.clear();};

};

int Monte_Carlo_Integral::mci(std::vector<double> b, const int t_end){
    /*
    b -> vector of (x,y) pairs
    size -> Number of (x,y) pairs
    samples -> vector of (x,y) monte-carlo samples
    N -> Number of monte-carlo samples
    */
    double s, x1, y1, x2, y2;

    // Returns a pointer to a quasi random numbers generator in 2 dimensions.
    // Note that quasi random sequences do not use a seed and always return the same sequence
    gsl_qrng * q = gsl_qrng_alloc(gsl_qrng_sobol, 2);

    // To count the number of samples that fall on a circle
    int counter = 0;

    double v[2];
    for(int i=0; i<N; i++){
        // Generate (x,y) pair
        gsl_qrng_get(q, v);
        x1 = L*v[0]; y1 = L*v[1];
        // Store
        samples.push_back(x1);
        samples.push_back(y1);
        // Check if it fell on a circle
        for(int j=0; j<t_end; j++){
            x2 = b[2*j]; y2 = b[2*j+1];
            s = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
            if(s<=R){
                counter++;
                break;
            }
        }
    }
    return counter;
}

void Monte_Carlo_Integral::print(std::vector<double> b, const int t_end, std::string circles_file, std::string samples_file){
    std::ofstream circles(circles_file);
    std::ofstream points(samples_file);
    for(int i=0; i<t_end; i++){
        circles << b[2*i] << "\t" << b[2*i+1] << std::endl;
    }
    for(int i=0; i<N; i++){
        points << samples[2*i] << "\t" << samples[2*i+1] << std::endl;
    }
    circles.close();
    points.close();
}

#endif // MONTE_CARLO_INTEGRAL_H_
