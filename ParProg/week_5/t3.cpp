#include <iostream>
#include <omp.h>
#include <vector>
#include <random>
#include <fstream>

#define OMPk

using namespace std;

int main(){
    int cores = 2;
#ifdef OMP
    //ofstream output_omp("data_for_t_plot/data_omp_int.txt");
    ofstream output_omp("data_for_t_plot/data_omp_int_cores.txt");
#else
    //ofstream output("data_for_t_plot/data_int.txt");
    ofstream output("data_for_t_plot/data_int_cores.txt");
#endif
    double h = 1e-9;
    while (cores < 3){
        double I = 0;
        double x = 0;
    #ifdef OMP
        double t0 = omp_get_wtime();
        #pragma omp parallel private(I)
        {
            #pragma omp for
                for (int i = 0; i < (int)(1/h); ++i){
                    I += 4.0 / (1 + i * h * i * h) * h;
                }
        }
        double t = omp_get_wtime();
        output_omp << cores << ' ' << t - t0 << endl;
        cores++;
    #else
        double t0 = omp_get_wtime();
        for (int i = 0; i < 1/h; ++i){
                    I += 4.0 / (1 + i * h * i * h) * h;
                }
        double t = omp_get_wtime();
        output << cores << ' ' << t - t0 << endl;
        cores++;
    #endif
    }

}