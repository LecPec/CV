#include <iostream>
#include <vector>
#include <omp.h>
#include <fstream>
#include <algorithm>
#include <math.h>

#define NY 20
#define NX 20

using namespace std;

void PrintVec(const vector<vector<double> > v);
void PrintVecParallel(const vector<vector<double> > v);
vector<vector<double> > PoissonSolver(int n, double eps);
vector<vector<double> > PoissonSolverPararallel(int n, double eps, int threads);