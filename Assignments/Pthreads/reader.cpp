#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

int data = 0;
int readerCount = 0;
sem_t mutex, rw_mutex;

void *writer(void *arg) {
    while (true) {
        sem_wait(&rw_mutex);
        data++;
        cout << "Data written by writer: " << data << endl;
        sem_post(&rw_mutex);
        // Simulating writer delay
        sleep(1);
    }
    pthread_exit(NULL);
}

void *reader(void *arg) {
    while (true) {
        sem_wait(&mutex);
        readerCount++;
        if (readerCount == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        cout << "Data read by reader: " << data << endl;

        sem_wait(&mutex);
        readerCount--;
        if (readerCount == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);
        // Simulating reader delay
        sleep(1);
    }
    pthread_exit(NULL);
}