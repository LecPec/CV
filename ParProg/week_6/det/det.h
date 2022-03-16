#include <iostream>
#include <omp.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <fstream>

#define DIM 10

using matrix = std::vector< std::vector<double> >;

using namespace std;

double Det(const matrix& A, int N_threads);
matrix DefineSubMatrix(const matrix& A, int j_curr);
void PrintMatrix(const matrix& A);