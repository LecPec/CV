#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int a = 0;
pthread_mutex_t mut;

void *mythread(void *value){
    pthread_t mythid;
    mythid = pthread_self();
    pthread_mutex_lock(&mut);
        a = a + 1;
        cout << "Daughter thread and result = " << mythid << " " << a << endl;
    pthread_mutex_unlock(&mut);    
    return 0;
}

int main(){
    pthread_t thid, mythid;
    int result;
    pthread_mutex_init(&mut, NULL);
    result = pthread_create(&thid, nullptr, mythread, nullptr);
    if (result != 0){
        cout << "Error on creating thread, return value = " << a << endl;
        exit(-1);
    }
    cout << "Thread created " << thid << endl;
    mythid = pthread_self();
    pthread_mutex_lock(&mut);
        a += 1;
    pthread_mutex_unlock(&mut);
    cout << "Main thread and result = " << mythid << " " << a << endl;
    pthread_mutex_destroy(&mut);
    return 0;

}