#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
using namespace std;
pthread_mutex_t mut;
void *ThrFunc(void *arg){
    pthread_t thid;
    pthread_mutex_lock(&mut);
        int* var = (int *) arg;
        thid = pthread_self();
        *var += 1;
    pthread_mutex_unlock(&mut);
    return NULL;
}

int main(){
    pthread_t thid, thid_;
    int var = 9;
    pthread_mutex_init(&mut, NULL);
    pthread_create(&thid, nullptr, ThrFunc, (void*) &var);
    cout << "Thread created " << thid << endl;

    thid_ = pthread_self();
    pthread_mutex_lock(&mut);
        cout << "Variable is " << var << endl;
    pthread_mutex_unlock(&mut);
    pthread_join(thid, NULL);
    pthread_mutex_destroy(&mut);
    return 0;
    
}