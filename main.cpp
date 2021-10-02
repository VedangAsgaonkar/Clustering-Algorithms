#include<iostream>
#include<map>
#include<iterator>
#include<cmath>
#include"point.h"
#include"kMeansEstimator.h"

int main(){
    srand48(12);
    double* x_list = new double[400];
    double* y_list = new double[400];
    for(int i=0 ; i<400 ; i++){        
        if(i<100){
            x_list[i] = -5 + 7*drand48();
            y_list[i] = -5 + 7*drand48();
        }
        else if(i<200){
            x_list[i] = -5 + 7*drand48();
            y_list[i] = 5 - 7*drand48();
        }
        else if(i<300){
            x_list[i] = 5 - 7*drand48();
            y_list[i] = -5 + 7*drand48();
        }
        else {
            x_list[i] = 5 - 7*drand48();
            y_list[i] = 5 - 7*drand48();
        }
    }
    std::cout << "type,x,y" << std::endl;
    kMeansEstimator* k = new kMeansEstimator(x_list,y_list,400);
    std::multimap<int,int> mp = k->cluster(4,20);    
    for(auto i = mp.begin() ; i!=mp.end() ; i++){
        std::cout << i->first << "," << x_list[i->second] << "," << y_list[i->second] << std::endl;
    }
}