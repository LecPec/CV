#include <iostream>
#include <omp.h>
#include <array>
#include <random>
#include <fstream>


using namespace std;

int main(){
    const size_t DIM = 99999999;
    vector<int> a;
    default_random_engine gen;
    uniform_int_distribution<> dis(-1000, 1000);
    int counter_omp = 0;
    int counter = 0;
#pragma omp parallel 
{
    #pragma omp for
        for (int i = 0; i < DIM; ++i){
            #pragma omp critical
            {
                a.push_back(dis(gen));
            }
        }
}
double t0 = omp_get_wtime();
#pragma omp parallel reduction(+ : counter_omp)
{
    #pragma omp for 
        for (int i = 0; i < DIM; ++i){
            if (a[i] % 6 == 0)
                counter_omp++;
        }
}
double t = omp_get_wtime();

double T0 = omp_get_wtime();
    for (int i = 0; i < DIM; ++i){
        if(a[i] % 6 == 0)
            counter ++;
    }
double T = omp_get_wtime();
    cout << "Without OpenMP : " << counter << " during " << T - T0 << " seconds" << endl;
    cout << "With OpenMP : " << counter_omp << " during " << t - t0 << " seconds" << endl;
}