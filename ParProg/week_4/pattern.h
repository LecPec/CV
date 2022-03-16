#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <iostream>
#include <vector>

#define NUM_OF_THREADS 3

using namespace std;

class ProdCons{
public:
    void* producer_routine(void* args);
    void* consumer_routine(void* args);
    void* interruptor_routine(void* args);
    int run_threads();

    vector<int> buffer;
    vector<pthread_t> threads;
    pthread_t prod;
    pthread_t cons;
    pthread_t interruptor;
    int sum;
    bool ready_to_consume;
};