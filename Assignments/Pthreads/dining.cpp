#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define N 5 // Number of philosophers

sem_t chopsticks[N];

void *philosopher(void *arg) {
    int philID = *((int *)arg);
    int leftChopstick = philID;
    int rightChopstick = (philID + 1) % N;

    while (true) {
        // Thinking
        cout << "Philosopher " << philID << " is thinking\n";
        sleep(1);

        // Attempt to pick up chopsticks
        sem_wait(&chopsticks[leftChopstick]);
        sem_wait(&chopsticks[rightChopstick]);

        // Eating
        cout << "Philosopher " << philID << " is eating\n";
        sleep(1);

        // Put down chopsticks
        sem_post(&chopsticks[leftChopstick]);
        sem_post(&chopsticks[rightChopstick]);
    }
    pthread_exit(NULL);
}
