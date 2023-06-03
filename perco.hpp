#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Random64.h>

#ifndef PERCO_H_
#define PERCO_H_

std::vector<double> create_system(Crandom &ran64, int L, int t){
    //b will save x(even),y(odd) coordinates for every circle
    std::vector<double> b;
    for(int i=0; i < t; i++){
        b.push_back(L*ran64.r()); //x
        b.push_back(L*ran64.r()); //y
    }
    return b;
}

void print_system(std::string filename, std::vector<double> &b){
    std::ofstream file(filename);
    file << "x\t" <<"y\t" <<std::endl;
    for(int i=0; i < b.size(); i+=2){
        file << b[i] << "\t" << b[i+1] <<std::endl;
    }
    file.close();
}

double find_t_cluster(std::vector<double> &b, int t_end, double R){
    double t=t_end/2;
    std::vector<int> clusters(b.size()/2,0);
    clusters[0]=1;
    double s,x1,y1,x2,y2,aux=2;
    for(int i=0; i < clusters.size(); i++){
        x1=b[2*i], y1=b[2*i+1];
        if(clusters[i]==0){
            clusters[i]=aux;
            aux++;
        }
        for(int j=i+1;j < clusters.size(); j++){
            x2=b[2*j], y2=b[2*j+1];
            s = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
            if(s<=2*R && clusters[j]==0) clusters[j]=clusters[i];
            else if(s<=2*R && clusters[j]<clusters[i]) clusters[i]=clusters[j];
        }
    }
    for(auto const &i: clusters){
        std::cout << i << std::endl;
    }
    return 5;
}

#endif // PERCO_H_
