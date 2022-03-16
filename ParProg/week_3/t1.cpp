#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int a = 0;

void *mythread(void *value){
    pthread_t mythid;
    mythid = pthread_self();
    a = a + 1;
    cout << "!!Thread and result = " << mythid << " " << a << endl;
    return 0;
}

void *mynewthread(void *value){
    pthread_t mynewthid;
    mynewthid = pthread_self();
    a = a + 3;
    cout << "**Thread and result = " << mynewthid << " " << a << endl;
    return 0;
}

int main(){
    pthread_t thid1, thid2, mythid, mynewthid;
    int result, newresult;
    result = pthread_create(&thid1, nullptr, mythread, nullptr);
    cout << "Thread 1 created " << thid1 << endl;
    if (result != 0){
        cout << "Error on thread creation, return value = " << result << endl;
        exit(-1);
    }
    mythid = pthread_self();
    sleep(1);
    a += 1;
    cout << "Result after main tread work " << a << endl;
    pthread_join(thid1, NULL);
    newresult = pthread_create(&thid2, nullptr, mynewthread, nullptr);
    cout << "Thread 2 created " << thid2 << endl;
    if (newresult != 0){
        cout << "Error on thread creation, return value = " << newresult << endl;
        exit(-1);
    }
    mynewthid = pthread_self();
    pthread_join(thid2, NULL);
    return 0;


}