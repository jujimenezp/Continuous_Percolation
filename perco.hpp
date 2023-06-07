#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Random64.h>

#ifndef PERCO_H_
#define PERCO_H_

class Percolacion{
    private:
        const int L, L2, t_end;
        const double R,D;
        std::vector<double> b;
        std::vector<int> clusters;
        std::vector<int> id;
        std::vector<int> papas;
    public:
        Percolacion(const int Li, const int t_endi, const double Ri) :
            L(Li), L2(L*L), t_end(t_endi), R(Ri), D(2*Ri) , id(t_endi,-1), papas(t_end,-1){}
        void create_system(Crandom &ran64);
        void print_system(std::string filename);
        int find(int i);
        void find_papas();
        void merge();
        void join(int p_i, int p_j);

};

void  Percolacion::create_system(Crandom &ran64){
    //b will save x(even),y(odd) coordinates for every circle
    // b.push_back(20); b.push_back(5);
    // b.push_back(10); b.push_back(25);
    for(int i=0; i < t_end; i++){
        b.push_back(L*ran64.r()); //x
        b.push_back(L*ran64.r()); //y
        // b.push_back(35-5*i);
        // b.push_back(25);
    }
    clusters.resize(b.size()/2,0);
}

void Percolacion::print_system(std::string filename){
    std::ofstream file(filename);
    file << "x\t" <<"y\t" << "cluster" <<std::endl;
    for(int i=0; i < b.size(); i+=2){
        file << b[i] << "\t" << b[i+1] <<"\t"<<papas[i/2]<<std::endl;
    }
    file.close();
}


int Percolacion::find(int i){
    //if i alredy has a parent just return it
    if(papas[i]!=-1) return papas[i];
    bool go_m=false; //Tells if we should calculate a parent's parent
    int j,papa=i; //if i doesn't have no parents it will be its own parent
    double s,x1,y1,x2,y2;
    x1=b[2*i], y1=b[2*i+1];
    for(int m=0;m < i;m++){
        x2=b[2*m], y2=b[2*m+1];
        // Measure distance between circles i and j
        s = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
        //if we find a parent go check their parent
        if(s <=D){
            go_m=true;
            j=m;
            break;
        }
    }
    if(go_m==true) papa=this->find(j);
    return papa;
}

void Percolacion::find_papas(){
    for(int i=0;i < t_end;i++){
        papas[i]=find(i);
    }
}

void Percolacion::merge(){
    double s,x1,y1,x2,y2,R2=2*R;
    for(int i=0;i < t_end;i++){
        x1=b[2*i], y1=b[2*i+1];
        for(int j=i+1; j < t_end; j++){
            x2=b[2*j], y2=b[2*j+1];
            // Measure distance between circles i and j
            s = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
            if(s <= D){
                if(papas[i] > papas[j]) this->join(papas[j],papas[i]);
                else if(papas[j] > papas[i]) this->join(papas[i],papas[j]);
            }
        }
    }
}

void Percolacion::join(int p_i, int p_j){
    for(int k=0; k < t_end;k++){
        if(papas[k]==p_j) papas[k]=p_i;
    }
}

#endif // PERCO_H_
