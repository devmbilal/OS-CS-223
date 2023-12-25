#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t agentSem, tobaccoSem, paperSem, matchSem, mutex;
bool isTobacco = false, isPaper = false, isMatch = false;

void *agent(void *arg) {
    while (true) {
        sem_wait(&agentSem);
        int item = rand() % 3;
        switch (item) {
            case 0:
                sem_post(&tobaccoSem);
                sem_post(&paperSem);
                break;
            case 1:
                sem_post(&paperSem);
                sem_post(&matchSem);
                break;
            case 2:
                sem_post(&matchSem);
                sem_post(&tobaccoSem);
                break;
        }
        sleep(1);
    }
    pthread_exit(NULL);
}


void *smoker_tobacco(void *arg) {
    while (true) {
        sem_wait(&tobaccoSem);
        sem_wait(&mutex);
        if (isPaper) {
            isPaper = false;
            sem_post(&agentSem);
        } else if (isMatch) {
            isMatch = false;
            sem_post(&agentSem);
        } else {
            isTobacco = true;
        }
        sem_post(&mutex);
        cout << "Smoker with tobacco is smoking\n";
        sleep(1);
    }
    pthread_exit(NULL);
}


// Implement similar functions for other smokers

int main() {
    pthread_t agentThread, smoker_tobaccoThread, smoker_paperThread, smoker_matchThread;

    sem_init(&agentSem, 0, 1);
    sem_init(&tobaccoSem, 0, 0);
    sem_init(&paperSem, 0, 0);
    sem_init(&matchSem, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&agentThread, NULL, agent, NULL);
    pthread_create(&smoker_tobaccoThread, NULL, smoker_tobacco, NULL);
    // Create threads for other smokers

    pthread_join(agentThread, NULL);
    pthread_join(smoker_tobaccoThread, NULL);
    // Join other smoker threads

    sem_destroy(&agentSem);
    sem_destroy(&tobaccoSem);
    sem_destroy(&paperSem);
    sem_destroy(&matchSem);
    sem_destroy(&mutex);

    return 0;
}