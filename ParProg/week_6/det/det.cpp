#include "det.h"

omp_lock_t det_lock;
omp_lock_t lock1;

void PrintMatrix(const matrix& A){
    ofstream out("matrix.txt");
    //out.clear();
    for (const auto& m : A){
        for (const auto& elem : m)
            out << elem << ' ';
        out << endl;
    }
        
}

matrix DefineSubMatrix(const matrix& A, int j_curr){
    matrix res;

    for (int i = 1; i < A.size(); ++i){
        vector<double> row;
        for (int j = 0; j < A[0].size(); ++j){
            if (j != j_curr)
                row.push_back(A[i][j]);
        }
        res.push_back(row);
        row.clear();
    }
    return res;
}

double Det(const matrix& A, int N_threads){    
    int n = A.size();
    //cout << n << endl;
    matrix tmp;
    for (int i = 0 ; i < A.size(); ++i)
        tmp.push_back(A[i]);
    double res = 0;

    if (n == 2){
        res = A[0][0] * A[1][1] - A[1][0] * A[0][1];
        //return res;
    }

    else{
        matrix sub_matrix;
        #pragma omp parallel reduction (+ : res) private (sub_matrix) num_threads(N_threads)
        {   
            #pragma omp for
            for (int j = 0; j < tmp.size(); ++j){
                sub_matrix = DefineSubMatrix(tmp, j);
                res += pow(-1, j) * tmp[0][j] * Det(sub_matrix, N_threads);
            }
        }
    }
    return res;
}