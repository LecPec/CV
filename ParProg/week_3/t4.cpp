#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <array>
#include <algorithm>
#include <sys/types.h>
#define DIM 6
using namespace std;
pthread_mutex_t mut;

void PrintArr(const array<int, DIM - 1>& arr){
    for (int i = 0; i < arr.size(); ++i){
        cout << arr[i] << ' ';
    }
    cout << endl;
}

class Data{
public:
    int lhs;
    int rhs;

    Data(){};
    Data(int lhs_, int rhs_, array<int, DIM> arr_){
        lhs = lhs_;
        copy(arr_.begin(), arr_.end(), arr.begin());
        SetArr(arr_);
        sum.fill(0);
    }
    void SetArr(array<int, DIM> arr_){
        arr = arr_;
    }
    void SetSum(int sum_, int idx){
        sum[idx] = sum_;
    }
    int GetArrElem(int idx){
        return arr[idx];
    }
    int GetSum(int idx){
        return sum[idx];
    }
    array<int, DIM - 1> GetSum_(){
        return sum;
    }
private:
    array<int, DIM> arr;
    array<int, DIM - 1> sum;
};

void *sum_of_neighbours(void *elems){
    pthread_mutex_lock(&mut);
        pthread_t thid = pthread_self();
        Data *pair = (Data *) elems;
        pair->SetSum(pair->GetArrElem(pair->rhs) + pair->GetArrElem(pair->lhs), pair->lhs);
        PrintArr(pair->GetSum_());
    pthread_mutex_unlock(&mut);
    return NULL;
}

int main(int argc, char **argv){
    int N = DIM;
    int arr[N];
    pthread_t Thid, thid[2];
    Data data;
    array<int, DIM> a;
    a.fill(2);
    data.SetArr(a);
    for (int i = 0; i < N-1; ++i){
        pthread_mutex_init(&mut, NULL);
        pthread_mutex_lock(&mut);
            data.lhs = i;
            data.rhs = data.lhs + 1;
        pthread_mutex_unlock(&mut);
        pthread_create(&thid[i], nullptr, sum_of_neighbours, (void*) &data);
        cout << "Thread created " << Thid << endl;
        cout << "////" << endl;
        Thid = pthread_self();
        pthread_join(thid[i], NULL);
        pthread_mutex_lock(&mut);
            cout << "Thread and value: " << thid[i] << ' ' << data.GetSum(i) << endl;
        pthread_mutex_unlock(&mut);
        pthread_mutex_destroy(&mut);
    }
    return 0;

}