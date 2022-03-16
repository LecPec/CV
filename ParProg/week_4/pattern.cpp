#include "pattern.h"

pthread_mutex_t mut;
pthread_cond_t cond_prod;
pthread_cond_t cond_cons;

int ProdCons::run_threads(){
    for (int i = 0; i < NUM_OF_THREADS; ++i){
        pthread_t thid;
        threads.push_back(thid); 
    }
    for (int i = 0; i < NUM_OF_THREADS; ++i){
        pthread_create(&threads[i], NULL, consumer_routine, NULL);
    }
    pthread_create(&prod, NULL, (void *)(producer_routine), NULL);
    pthread_create(&interruptor, NULL, interruptor_routine, NULL);

    pthread_join(prod, NULL);
    pthread_join(interruptor, NULL);

    for (int i = 0; i < NUM_OF_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    return sum;
}

void* producer_routine(void* args){
    pthread_mutex_init(&mut, NULL);

    pthread_mutex_destroy(&mut);
}