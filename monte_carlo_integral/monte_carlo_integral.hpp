#ifndef MONTE_CARLO_INTEGRAL_H_
#define MONTE_CARLO_INTEGRAL_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_qrng.h>

const int L=50;
const double R=4;
const double D=2*R;

void generate(std::vector<double> & b, int t_end, int SEED);
int monte_carlo_integral(std::vector<double> & b, int t_end, std::vector<double> & samples, int N);
void print(std::vector<double> & b, std::vector<double> & samples, int t_end, int N);


void generate(std::vector<double> & b, int t_end, int SEED){
    /*
    b -> array to be filled with (x,y) pairs
    t_end -> Number of pairs
    SEED -> Seed
    */

    // Random numbers generator
    gsl_rng * r = gsl_rng_alloc(gsl_rng_ranlux); // Returns a pointer to the generator
    gsl_rng_set(r, SEED); // Seeds the generator
    // Fill array
    for(int i=0; i<t_end; i++){
        b.push_back(L*gsl_rng_uniform_pos(r)); // double between (0,1) exclusive
        b.push_back(L*gsl_rng_uniform_pos(r));
    }
    gsl_rng_free(r); // Releases memory
}

int monte_carlo_integral(std::vector<double> & b, int t_end, std::vector<double> & samples, int N){
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

void print(std::vector<double> & b, std::vector<double> & samples, int t_end, int N){
    std::ofstream circles("circles_coords.dat");
    std::ofstream points("monte-carlo_points.dat");
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
