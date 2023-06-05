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
        const double R;
        std::vector<double> b;
        std::vector<int> clusters;
    public:
        Percolacion(const int Li, const int t_endi, const double Ri) :
            L(Li), L2(L*L), t_end(t_endi), R(Ri) {}
        void create_system(Crandom &ran64);
        void print_system(std::string filename);
        void find_t_cluster();
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
        file << b[i] << "\t" << b[i+1] <<"\t"<<clusters[i/2]<<std::endl;
    }
    file.close();
}

void Percolacion::find_t_cluster(){
    //double t=t_end/2;
    std::vector<bool> check_up(clusters.size(),false);
    std::vector<bool> check_down(clusters.size(),false);
    clusters[0]=1;
    double s,x1,y1,x2,y2,vec_aux=0;
    int aux=2, reorder_carry;
    int R2 = 2*R;
    for(int i=0; i < clusters.size(); i++){
        x1=b[2*i], y1=b[2*i+1];
        reorder_carry=1;
        if(clusters[i]==0){
            clusters[i]=aux;
            aux++;
        }
        // Check if circle i touches upper or lower boundary
        if(y1+R >= L) check_up[clusters[i]]=true;
        if(y1 <= R) check_down[clusters[i]]=true;
        //Check for next circles
        for(int j=i+1;j < clusters.size(); j++){
            x2=b[2*j], y2=b[2*j+1];
            // Measure distance between circles i and j
            s = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
            if(s <= R2){
                check_up[clusters[i]]=check_up[clusters[j]]=check_up[clusters[i]] || check_up[clusters[j]];
                check_down[clusters[i]]=check_down[clusters[j]]=check_down[clusters[i]] || check_down[clusters[j]];
                if(clusters[j]==0) clusters[j]=clusters[i];
                else if(clusters[j]<clusters[i]) clusters[i]=clusters[j];
                //Reorder clusters vector
                vec_aux=clusters[j];
                clusters[j]=clusters[i+reorder_carry];
                clusters[i+reorder_carry]=vec_aux;
                //Reorder b vector
                vec_aux=b[2*j]; b[2*j]=b[2*(i+reorder_carry)]; b[2*(i+reorder_carry)]=vec_aux;
                vec_aux=b[2*j+1]; b[2*j+1]=b[2*(i+reorder_carry)+1]; b[2*(i+reorder_carry)+1]=vec_aux;
                reorder_carry++;
            }
        }
    }
    for(auto const &i: clusters){
        std::cout << i << std::endl;
    }
}

#endif // PERCO_H_
