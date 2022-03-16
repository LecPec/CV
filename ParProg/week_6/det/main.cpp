#include "det.h"

int main(){
    matrix A;

    vector<double> row;
    default_random_engine rd;
    uniform_int_distribution<> distr(-5, 5);
    ofstream out("determinant_data_from_dim_posl.txt");
    for (int dim = 2; dim < 15; dim += 1){
        for (int i = 0; i < dim; ++i){
            for (int j = 0; j < dim; j++){
                row.push_back(distr(rd));
            }
            A.push_back(row);
            row.clear();
        }
    //if (A.size() != A[0].size())
      //m  throw "n != m";
    //PrintMatrix(A);
        double t0 = omp_get_wtime();
        cout << Det(A, 1) << endl;
        double t = omp_get_wtime();
        out << dim << ' ' << t - t0 << endl;
        A.clear();
    }
}