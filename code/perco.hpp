#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Random64.h>

#ifndef PERCO_H_
#define PERCO_H_

class Percolacion3D{
    private:
        const int L, L3, t_end;
        const double R,D;
        bool percolante;
        std::vector<double> b;
        std::vector<int> papas;
        std::vector<bool> check_up;
        std::vector<bool> check_down;

    public:
        Percolacion3D(const int Li, const int t_endi, const double Ri) :
            L(Li), L3(L*L*L), t_end(t_endi), R(Ri), D(2*Ri), percolante(false),
            papas(t_endi,-1), check_up(t_endi,false), check_down(t_endi,false){}
        void create_system(Crandom &ran64);
        void print_system(std::string filename,int t);
        int find(int i);
        void find_papas(int t);
        void merge(int t);
        void join(int p_i, int p_j,int t);
        int t_percolante();
        void check_percolancia(int i);
        void reset_clusters();
        std::vector<double> get_b(){return b;}
};

void  Percolacion3D::create_system(Crandom &ran64){
    //b will save x, y, and z coordinates for every circle
    for(int i=0; i < t_end; i++){
        b.push_back(L*ran64.r()); //x
        b.push_back(L*ran64.r()); //y
        b.push_back(L*ran64.r()); //z
    }
}

void Percolacion3D::print_system(std::string filename, int t){
    std::ofstream file(filename);
    file << "x\t" <<"y\t" << "z\t"<<"cluster" <<std::endl;
    for(int i=0; i < 3*t; i+=3){
        file << b[i] << "\t" << b[i+1] <<"\t"<<b[i+2]<<papas[i/3]<<std::endl;
    }
    file.close();
}


int Percolacion3D::find(int i){
    //if i alredy has a parent just return it
    if(papas[i]!=-1) return papas[i];
    bool go_m=false; //Tells if we should calculate a parent's parent
    int j,papa=i; //if i doesn't have no parents it will be its own parent
    double s,x1,y1,z1,x2,y2,z2;
    x1=b[3*i], y1=b[3*i+1], z1=b[3*i+2];
    for(int m=0;m < i;m++){
        x2=b[3*m], y2=b[3*m+1],z2=b[3*m+2];
        // Measure distance between circles i and j
        s = sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2));
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

void Percolacion3D::find_papas(int t){
    for(int i=0;i < t;i++){
        papas[i]=find(i);
        this->check_percolancia(i);
    }
}

void Percolacion3D::merge(int t){
    double s,x1,y1,z1,x2,y2,z2;
    for(int i=0;i < t;i++){
        x1=b[3*i], y1=b[3*i+1],z1=b[3*i+2];
        for(int j=i+1; j < t; j++){
            x2=b[3*j], y2=b[3*j+1], z2=b[3*j+2];
            // Measure distance between circles i and j
            s = sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2));
            if(s <= D){
                if(papas[i] > papas[j]) this->join(papas[j],papas[i],t);
                else if(papas[j] > papas[i]) this->join(papas[i],papas[j],t);
            }
        }
        this->check_percolancia(i);
    }
}

void Percolacion3D::join(int p_i, int p_j, int t){
    for(int k=0; k < t;k++){
        if(papas[k]==p_j) papas[k]=p_i;
    }
    check_up[p_i] = check_up[p_i] || check_up[p_j];
    check_down[p_i] = check_down[p_i] || check_down[p_j];
}

int Percolacion3D::t_percolante(){
    int t=t_end, a=0, b=t_end;
    this->find_papas(t);
    this->merge(t);
    if(percolante==false){
        std::cout << "No hay cluster percolante en el tiempo final!!\nIntento Terminado." <<std::endl;
        return 0;
    }
    t=t/2;
    while(b-a>1){
        this->reset_clusters();
        this->find_papas(t);
        this->merge(t);
        if(percolante==true) b=t;
        else a=t;
        t=(a+b)/2;
    }
    this->reset_clusters();
    this->find_papas(t);
    this->merge(t);
    if(percolante==true) return t;
    else{
        this->find_papas(t+1);
        this->merge(t+1);
        return t+1;
    }
}

void Percolacion3D::check_percolancia(int i){
     if(b[3*i+2]+R>=L) check_up[papas[i]]=true;
     if(b[3*i+2]<=R) check_down[papas[i]]=true;
     if(check_up[papas[i]] && check_down[papas[i]]){
         // std::cout << "Cluster percolante! " << "\n"
         //           << "Cluster: " << papas[i] <<std::endl;
         percolante=true;
         return;
     }
     return;
}

void Percolacion3D::reset_clusters(){
    percolante=false;
    std::fill(check_up.begin(),check_up.end(),false);
    std::fill(check_down.begin(),check_down.end(),false);
    std::fill(papas.begin(),papas.end(),-1);
}

#endif // PERCO_H_
