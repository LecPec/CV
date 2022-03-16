#include <iostream>
#include <omp.h>
#include <array>
#include <random>

#define DIM 600

using namespace std;

void PrintArr(const array<double, DIM>& a){
    for (const auto& elem : a)
        cout << elem << ' ';
    cout << endl;
}

int main(){
    array <double, DIM> a;
    array<double, DIM> b;
    array<double, DIM> sum;

    default_random_engine gen;
    uniform_real_distribution<> dis(-100, 100);

    for (int i = 0; i < DIM; ++i){
        a[i] = dis(gen);
        b[i] = dis(gen);
    }

#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < DIM; ++i){
            sum[i] = a[i] + b[i];
        }  
    }
    PrintArr(sum);


    return 0;
}