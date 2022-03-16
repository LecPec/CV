#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <vector>

#define NUM_OF_THREADS 3
 
using namespace std;

void* producer_routine(void* arg);
void* consumer_routine(void* arg);
void* consumer_interruptor_routine(void* arg);
int run_threads();
void produce_num(int n);
void set_buffer(vector<int>& buffer_init);
