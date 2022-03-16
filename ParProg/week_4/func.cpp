#include "func.h"

pthread_mutex_t mut;
pthread_cond_t cond;
bool ready_to_consume = false;
int sum = 0;
int num = 0;
bool consumers_started = false;
vector<int> buffer;
int cons_count = 0;

void PrintVec(const vector<int>& v){
    for (const auto& v_ : v)
        cout << v_ << ' ';
    cout << endl;
}

int run_threads(){
    pthread_t producer_thid, interrupter_thid, thids[NUM_OF_THREADS];
    pthread_create(&producer_thid, NULL, &producer_routine, NULL);
    pthread_create(&interrupter_thid, NULL, &consumer_interruptor_routine, NULL);
    for (int i = 0; i < NUM_OF_THREADS; ++i){
        pthread_create(&thids[i], NULL, &consumer_routine, NULL);
    }
    consumers_started = true;

    pthread_join(producer_thid, NULL);
    pthread_join(interrupter_thid, NULL);
    for (int i = 0; i < NUM_OF_THREADS; ++i){
        pthread_join(thids[i], NULL);
    }
    return 0;
}
void produce_num(){
    int n = 0;
    cin >> n;
    cout << n << " was fed" << endl;
    buffer.push_back(n);
    PrintVec(buffer);
}
void* producer_routine(void* arg){
    while(true){
        pthread_mutex_init(&mut, NULL);
            pthread_mutex_lock(&mut);
                if (cons_count > 0)
                    break;
                produce_num();
                ready_to_consume = true;
            pthread_mutex_unlock(&mut);
            pthread_cond_signal(&cond);
        pthread_mutex_destroy(&mut);
    }
    while (ready_to_consume){
        pthread_cond_wait(&cond, &mut);
    }
    return NULL;
}
void* consumer_routine(void* arg){
    while(ready_to_consume == false){
        pthread_cond_wait(&cond, &mut);
    }
    pthread_mutex_init(&mut, NULL);
        pthread_mutex_lock(&mut);
        cons_count++;
        cout << "Data consumed: " << buffer.back() << endl;
        sum += buffer.back();
        buffer.pop_back();
        ready_to_consume = false;
        pthread_mutex_unlock(&mut);
    pthread_mutex_destroy(&mut);
    return NULL;
}
void* consumer_interruptor_routine(void* arg){
    while (!consumers_started)
        pthread_cond_wait(&cond, &mut);
    return NULL;
    
}