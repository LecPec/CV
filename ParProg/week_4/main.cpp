#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <sys/time.h>
#include <random>
//#include <cstdlib>

using namespace std;

pthread_mutex_t mut;
pthread_t Thid;
bool flag = false;
bool consumer_started = false;
int counter_of_consumed_values = 0;
int num_of_loops = 0;
int sum = 0;
vector<int> buffer;
pthread_cond_t cond_pr;
pthread_cond_t cond_cnsm;
vector<int> res;
bool buff_is_empty = true;

struct ConsData{
    double time;
    int num;
};

vector<int> GetVec(){
    int gotted;
    vector<int> v;
    while (cin >> gotted){
        if (gotted == 0)
            break;
        v.push_back(gotted);
    }
    return v;
}

void PrintVec(const vector<int>& v){
    cout << "Buffer: ";
    for (const auto& v_ : v)
        cout << v_ << ' ';
    cout << endl;
}

int produce_num(vector<int>& v){
    int n = 0;
    n = v.back();
    v.pop_back();
    return n;
}

void consume_data(int num){
    sum += num;
}

void* producer_routine(void* arg){
    vector<int> vec = *(vector<int>* )arg;
    num_of_loops = vec.size();
    int i = 0;

    while (!consumer_started){
        pthread_cond_wait(&cond_pr, &mut);
    }
    while(i < num_of_loops){
        pthread_mutex_lock(&mut);
        buffer.push_back(vec[i]);
        cout << vec[i] << " was added to buffer" << endl;
        buff_is_empty = false;
        pthread_cond_broadcast(&cond_cnsm);
        pthread_cond_wait(&cond_pr, &mut);
        flag = false;
        i++;
        pthread_mutex_unlock(&mut);
    }


    return NULL;
}

void* consumer_routine(void* arg){
    pthread_cond_t cond_cnsm;
    ConsData *data = (ConsData* )arg;
    struct timeval tv;
    struct timespec ts;
    gettimeofday(&tv, NULL);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, data->time);
    ts.tv_sec = time(NULL) + dis(gen) * 1000;

    while (buff_is_empty)
        pthread_cond_wait(&cond_cnsm, &mut);
    
    if (1){
        pthread_mutex_lock(&mut);
        if (buffer.size() == 0){
            cout << "Thread " << pthread_self() << " is waiting" << endl;
            pthread_cond_wait(&cond_cnsm, &mut);
        }
        sum += buffer.back();
        cout << "Sum was increased by " << buffer.back() << endl;
        pthread_cond_broadcast(&cond_pr);
        counter_of_consumed_values ++;
        flag = true;
        buff_is_empty = true;
        pthread_cond_timedwait(&cond_cnsm, &mut, &ts);

        pthread_mutex_unlock(&mut);

    }


    return NULL;
}

int run_threads(int N, ConsData& data, vector<int>& v){
    pthread_t cons[N];
    for (int i = 0; i < N; ++i){
        pthread_create(&cons[i], NULL, &consumer_routine, (void* ) &data);
        consumer_started = true;
    }
    Thid = pthread_self();
    for (int i = 0; i < N; ++i){
        pthread_join(cons[i], NULL);
    }
    return 0;
}

int main(int argc, char* argv[]){
    vector<int> init_vec;
    ConsData data = {atof(argv[1]), argc};
    init_vec = GetVec();
    pthread_t producer;
    pthread_create(&producer, NULL, producer_routine, (void* ) &init_vec);
    pthread_mutex_init(&mut, NULL);
    run_threads(data.num, data, init_vec);
    pthread_join(producer, NULL);
    pthread_mutex_destroy(&mut);
    cout << sum << endl;


    return 0;
}