#include "system.h"
omp_lock_t sys_lock;

void PrintVector(const vector<double>& vec){
    ofstream x_out("solution.txt");

    for (const auto& v : vec){
        x_out << v << ' ';
    }
    x_out << endl;
}

vector<double> Gauss(matrix& A, vector<double> b, int NUM_TH){
    ofstream out("new_matr.txt");
    ofstream out_b("new_b.txt");
    vector<double> x;
    int N = b.size();

    for (int i = 0; i < A.size(); ++i)
        x.push_back(0);

    /*if (N == M){
        if (Det(A, 12) == 0)
            throw "Matrix is degenerate";
    }*/

    matrix new_A;
    vector<double> new_b;
    vector<double> tmp_row;

    vector<int> non_zero_num;
    double non_zero_value;
    for (int num_of_iter = 0; num_of_iter < A.size(); ++num_of_iter){
        for (int row = num_of_iter; row < A.size(); ++row){
            for (int col = num_of_iter; col < A.size(); ++col){
                tmp_row.push_back(A[row][col]);
            }
            new_A.push_back(tmp_row);
            tmp_row.clear();
            new_b.push_back(b[row]);
        }

        
        for(int num_in_col = 0; num_in_col < new_A.size(); num_in_col++){
            if (new_A[0][num_in_col] != 0){
                non_zero_value = new_A[0][num_in_col];
                non_zero_num.push_back(num_in_col);
            }
        } // first non zero value in the first column was found

        vector<double> tmp = new_A[non_zero_num[0]];
        new_A[non_zero_num[0]] = new_A[0];
        new_A[0] = tmp; //swapped first row and row which is first to contain non zero value in first column
        non_zero_num.clear();

        double tmp_b = new_b[0];
        new_b[0] = new_b[non_zero_num[0]];
        new_b[non_zero_num[0]] = tmp_b;
        double koeff;
            ///// Making all numbers in the first column zero //////
        vector<double> tmp_vec;

        #pragma omp parallel shared(new_A) num_threads(NUM_TH)
        {
            #pragma omp for 
            for (int row = 1; row < new_A.size(); ++row){
                koeff = new_A[row][0] / new_A[0][0];
                new_b[row] -= koeff * new_b[0];
                #pragma omp parallel for
                for (int col = 0; col < new_A.size(); ++col){
                    new_A[row][col] -= koeff * new_A[0][col];
                }
            }
            #pragma omp for collapse(2) 
            for (int i = 1; i < new_A.size(); ++i){
                b[i + num_of_iter] = new_b[i];
                for(int j = 0; j < new_A.size(); ++j){
                    A[i + num_of_iter][j + num_of_iter] = new_A[i][j];
                }
            }
        }

        new_A.clear();
        new_b.clear();
            
        for (int i = 0; i < A.size(); ++i){
            for (int j = 0; j < A.size(); ++j){
                out << A[i][j] << ' ';
            }
            out_b << b[i] << endl;
            out << endl;
        }
        
    }
    //omp_destroy_lock(&sys_lock);

    //<<<<<<< At this moment the given matrix has been transformed into a step view >>>>>>>>//
    //<<<<<<< Now calculating x from the step view matrix >>>>>>>//

    x[N - 1] = b[N - 1] / A[N - 1][N - 1];
    double sum_k = 0;
    #pragma omp parallel private(sum_k) num_threads(NUM_TH)
    {
        #pragma omp for
        for (int k = N - 2; k > -1; k--){
            for (int i = k + 1; i < N ; ++i)
                sum_k += x[i] * A[k][i];
            x[k] = 1 / A[k][k] * (b[k] - sum_k);
            sum_k = 0;
        }
    }

    return x;


    }

    

