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