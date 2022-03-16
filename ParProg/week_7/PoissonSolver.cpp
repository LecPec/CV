#include "PoissonSolver.h"

void PrintVec(const vector<vector<double> > v){
    ofstream fout("output/solution.txt");
    for (const auto& row : v){
        for (const auto& x : row){
            fout << x << ' '; 
        }
        fout << endl;
    }
}

void PrintVecParallel(const vector<vector<double> > v){
    ofstream fout("output/solution_par.txt");
    for (const auto& row : v){
        for (const auto& x : row){
            fout << x << ' '; 
        }
        fout << endl;
    }
}

vector<vector<double> > PoissonSolver(int n, double eps){
    vector<vector<double> > uk;
    vector<vector<double> > uk_1;
    vector<vector<double> > du_k;
    vector<double> tmp_du;
    vector<double> max_in_du;
    vector<double> max_in_uk_1;
    double du_ = -9999999;
    double uk_1_ = -999999;
    vector<double> row; 
    vector<vector<double> > f;
    vector<double> fi;
    double hx = 1 / (double)n;
    double hy = 1 / (double)n;
    vector<double> x;
    vector<double> y;

    //ofstream fout("output/posl_err.txt", ofstream::app);

    for (int i = 0; i < n + 1; ++i){
        for (int j = 0; j < 2 * n + 1; ++j){
            row.push_back(0.0);
        }
        uk.push_back(row);
        uk_1.push_back(row);
        row.clear();
    }

    for (int i = 0; i < n + 1; i++){
        x.push_back(i * hx);
    }
    for (int j = 0; j < n * 2 + 1; ++j){
        y.push_back(j * hy);
    }

    for (int i = 0; i < n + 1; ++i){
        uk[i][2 * n] = 4 * x[i] * x[i]; 
    }
    for (int j = 0; j < 2 * n + 1; ++j){
        uk[n][j] = y[j] * y[j];
    }

    for (int i = 0; i < n + 1; ++i){
        for (int j = 0; j < 2 * n + 1; ++j){
            fi.push_back(x[i] * x[i] + y[j] * y[j]);
        }
        f.push_back(fi);
        fi.clear();
    }
    int k = 0;
    double error = 99999;
    while (error > eps){
        du_k.clear();
        for (int i = 1; i < n; i++){
            for (int j = 1; j < 2 * n; j++){
                uk[i][j] = 0.25 * (uk_1[i + 1][j] + uk[i - 1][j] + uk_1[i][j + 1] + uk[i][j - 1] - hx * hx * f[i][j]);
            }
        }

        for (int i = 0; i < n - 1; ++i){
            for (int j = 0; j < 2 * n - 1; ++j){
                tmp_du.push_back(fabs(uk[i][j] - uk_1[i][j]));
            }
            du_k.push_back(tmp_du);
            tmp_du.clear();
        }
        
        if(k != 0){
            for (int i = 0; i < n - 1; ++i){
                for (int j = 0; j < n - 1; ++j){
                    if (du_k[i][j] > du_ and du_k[i][j] != 0){
                        du_ = du_k[i][j];
                    }
                    if (fabs(uk_1[i][j]) > uk_1_ and uk_1[i][j] != 0){
                        uk_1_ = fabs(uk_1[i][j]);
                    }
                }
            }
            error = du_ / uk_1_;
        }
        uk_1 = uk;
        du_ = 0, uk_1_ = 0;
        k ++;
    }
    cout << k << endl;
    return uk;
}

vector<vector<double> > PoissonSolverPararallel(int n, double eps, int threads){
    vector<vector<double> > uk;
    vector<vector<double> > uk_1;
    vector<vector<double> > du_k;
    vector<double> tmp_du;
    vector<double> max_in_du;
    vector<double> max_in_uk_1;
    double du_ = -9999999;
    double uk_1_ = -999999;
    vector<double> row; 
    vector<vector<double> > f;
    vector<double> fi;
    double hx = 1 / (double)n;
    double hy = 1 / (double)n;
    vector<double> x;
    vector<double> y;

    //ofstream fout("output/par_err.txt", ofstream::app);

    for (int i = 0; i < n + 1; ++i){
        for (int j = 0; j < 2 * n + 1; ++j){
            row.push_back(0.0);
        }
        uk.push_back(row);
        uk_1.push_back(row);
        row.clear();
    }

    for (int i = 0; i < n + 1; i++){
        x.push_back(i * hx);
    }
    for (int j = 0; j < n * 2 + 1; ++j){
        y.push_back(j * hy);
    }

    for (int i = 0; i < n + 1; ++i){
        uk[i][2 * n] = 4 * x[i] * x[i]; 
    }
    for (int j = 0; j < 2 * n + 1; ++j){
        uk[n][j] = y[j] * y[j];
    }

    for (int i = 0; i < n + 1; ++i){
        for (int j = 0; j < 2 * n + 1; ++j){
            fi.push_back(x[i] * x[i] + y[j] * y[j]);
        }
        f.push_back(fi);
        fi.clear();
    }
    int k = 0;
    double error = 99999;
    while (error > eps){
        du_k.clear();
        #pragma omp parallel num_threads(threads)
        {   
            #pragma omp for schedule(dynamic)
            for (int i = 1; i < n; i++){
                for (int j = 1; j < 2 * n; j++){
                    uk[i][j] = (0.25 * (uk_1[i + 1][j] + uk[i - 1][j] + uk_1[i][j + 1] + uk[i][j - 1] - hx * hx * f[i][j]));
                }
            }

        }
        for (int i = 0; i < n - 1; ++i){
            for (int j = 0; j < 2 * n - 1; ++j){
                tmp_du.push_back(fabs(uk[i][j] - uk_1[i][j]));
            }
            du_k.push_back(tmp_du);
            tmp_du.clear();
        }
        if(k != 0){
            #pragma omp parallel for num_threads(threads) collapse(2)
            {
                for (int i = 0; i < n - 1; ++i){
                    for (int j = 0; j < n - 1; ++j){
                        if (du_k[i][j] > du_ and du_k[i][j] != 0){
                            du_ = du_k[i][j];
                        }
                        if (fabs(uk_1[i][j]) > uk_1_ and uk_1[i][j] != 0){
                            uk_1_ = fabs(uk_1[i][j]);
                        }
                    }
                }
            }
                error = du_ / uk_1_;
        }
        uk_1 = uk;
        du_ = 0, uk_1_ = 0;
        k ++;
    }
    cout << k << endl;
    //fout << n << ' ' << k << endl;;
    return uk;
}
