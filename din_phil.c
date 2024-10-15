#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NPHIL 5 
sem_t forks[NPHIL];

void *philosopher(void *arg) {
  int id = *(int *)arg;
  while(1) {
    // thinking
    printf("Philosopher %d is thinking.\n", id);
    sleep(1);
    // hungry
    printf("Philosopher %d is hungry and trying to pick up forks.\n", id);
    // picks his forks
    sem_wait(&forks[id]);
    sem_wait(&forks[(id + 1) % NPHIL]);
    // eats
    printf("Philosopher %d is eating.\n", id);
    sleep(2); 
    // leaving forks
    sem_post(&forks[id]);
    sem_post(&forks[(id + 1) % NPHIL]);
  }
  return NULL;
}

int main() {
  pthread_t philosophers[NPHIL];
  int ids[NPHIL];
  
  for (int i=0; i<NPHIL; i++) {
    sem_init(&forks[i], 0, 1); 
    ids[i] = i;   
  }
  
  for (int i=0; i<NPHIL; i++) {
    pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
  }
  
  for (int i=0; i<NPHIL; i++) {
    pthread_join(philosophers[i], NULL);
  }
  
  for (int i=0; i<NPHIL; i++) {
    sem_destroy(&forks[i]);
  }
  return 0; 
}
