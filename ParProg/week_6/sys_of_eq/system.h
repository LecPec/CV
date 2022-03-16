#include <iostream>
#include <vector>
#include <utility>
#include <omp.h>
#include <map>
#include "../det/det.h"
using namespace std;
using matrix = vector<vector<double> >;


vector<double> Gauss(matrix& A, vector<double> b, int NUM_TH);
void PrintVector(const vector<double>& vec);