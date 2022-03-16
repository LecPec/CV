#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <array>
#include <algorithm>
#include <sys/types.h>
#define DIM 3
using namespace std;
pthread_mutex_t mut;
double scalar_mult = 0.0;

struct Pair{
    double a;
    double b;
    double multi;
};

void *MultiThread(void *args){
    pthread_t thid;
    pthread_mutex_lock(&mut);
        thid = pthread_self();
        Pair* a_b = (Pair* ) args;
        a_b->multi = a_b->a * a_b->b;
    pthread_mutex_unlock(&mut);
    return NULL;
}

int main(){
    pthread_t Thid, thid[DIM];
    array<double, DIM> a = {1, 2, 3};
    array<double, DIM> b = {4, 5, 6};
    array<Pair, DIM> pairs;
    for (int i = 0; i < DIM; ++i){
        pairs[i].a = a[i];
        pairs[i].b = b[i];
        pthread_mutex_init(&mut, NULL);
        pthread_create(&thid[i], NULL, MultiThread, (void*) &pairs[i]);
        cout << "Thread created " << thid[i] << endl;
        Thid = pthread_self();
        pthread_join(thid[i], NULL);
        pthread_mutex_lock(&mut);
            scalar_mult += pairs[i].multi;
            cout << scalar_mult << endl;
        pthread_mutex_unlock(&mut);
        pthread_mutex_destroy(&mut);
    } 
    cout << "(a, b) = " << scalar_mult << endl; 
    return 0;


}