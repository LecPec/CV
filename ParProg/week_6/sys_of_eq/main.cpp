#include "system.h"

int main(){
    matrix A;
    vector<double> row;
    vector<double> b;
    vector<double> x;
    default_random_engine gen;
    uniform_int_distribution<> dis(-10, 10);
    ofstream out("sys_dim_posl.txt", std::ofstream::app);
    

    int N = 1;

    b.clear();
    x.clear();
    for (int n = 2; n< 251 ; n+=1){
        for (int i = 0; i < n; ++i){
            b.push_back(1);
        }

        for (int i = 0; i < n * n; ++i){
            row.push_back(dis(gen)); 

            if ((i + 1) % n == 0){
                A.push_back(row);
                row.clear();
            }
        }
        PrintMatrix(A);
        double t0 = omp_get_wtime();
        x = Gauss(A, b, N);
        double t = omp_get_wtime();
        out << n << ' ' << t - t0 << endl;
        PrintVector(x);
        A.clear();
        b.clear();
    }
    A.clear();

}