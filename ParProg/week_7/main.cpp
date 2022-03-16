#include "PoissonSolver.h"

int main(){
    vector<vector<double> > uij;
    vector<vector<double> > uij_par;
    int n = 100;
    ofstream time("output/time.txt");

    //uij = PoissonSolver(n, 1e-5);
    for (int threads = 1; threads < 17; ++ threads){
        double t0 = omp_get_wtime();
        uij_par = PoissonSolverPararallel(n, 1e-5, threads);
        double t = omp_get_wtime();
        time << threads << ' ' << t - t0 << endl;
    }
    //uij_par = PoissonSolverPararallel(n, 1e-5, 1);
    //PrintVec(uij);
    PrintVecParallel(uij_par);
}