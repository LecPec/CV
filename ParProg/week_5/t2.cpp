#include <iostream>
#include <omp.h>
#include <vector>
#include <random>
#include <fstream>

//#define DIM 60000
#define OMPk

using namespace std;

int main(){
    #ifdef OMP
            //ofstream output_omp("data_for_t_plot/data_omp.txt");
            ofstream omp_cores("data_for_t_plot/data_cores.txt");
    #else
            //ofstream output("data_for_t_plot/data.txt");
            ofstream output_cores("data_for_t_plot/data_cores_posl.txt");
    #endif

    for (int cores = 2; cores < 9; cores += 1){
        vector<double> a;
        vector<double> b;
        double scalar_multi = 0;

        default_random_engine gen;
        uniform_real_distribution<> dis(-100, 100);

        for (int i = 0; i < 100000; ++i){
            a.push_back(dis(gen));
            b.push_back(dis(gen));
        }

    #ifdef OMP
        double time0 = omp_get_wtime();
        #pragma omp parallel reduction(+ : scalar_multi) num_threads(cores)
            {
        #pragma omp for
                for (int i = 0; i < a.size(); ++i){
                    scalar_multi += a[i] * b[i];
                }
            }
            double time = omp_get_wtime();
            //output_omp << DIM << ' ' << time - time0 << endl;
            omp_cores << cores << ' ' << time - time0 << endl;
    #else
        double time0 = omp_get_wtime();
        for (int i = 0; i < 100000; ++i){
            scalar_multi+= a[i] * b[i];
        }
        double time = omp_get_wtime();
        output_cores << 100000 << ' ' << time - time0 << endl;
    #endif



        //cout << "time for parallel = " << time - time0 << endl;

        cout << "scalar multi = " << scalar_multi << endl;
    }
}
