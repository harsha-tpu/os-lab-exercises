#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NPHIL 5 // No of philosophers
#define LEFT (id + NPHIL - 1) % NPHIL // to get left chopstick
#define RIGHT (id + 1) % NPHIL // to get right chopstick
// states representing philosopher actions
#define THINKING 0 
#define HUNGRY 1 
#define EATING 2 

// global semaphore and state array 
sem_t mutex; 
sem_t phil[NPHIL]; 
int state[NPHIL];

void takeForks(int);
void putForks(int);
void test(int); // test if a philosopher can eat

void *philosopher(void *arg) {
  int id = *(int *)arg;
  takeForks(id);
  printf("Philosopher %d is eating.\n", id);
  sleep(3);
  putForks(id);
  printf("Philosopher %d is finished  eating.\n", id);
  return NULL;
}

void putForks(int id) {
  sem_wait(&mutex);
  state[id] = THINKING; 
  test(LEFT);
  test(RIGHT);
  sem_post(&mutex);
}

void takeForks(int id) {
  sem_wait(&mutex);
  state[id] = HUNGRY;
  test(id);
  sem_post(&mutex);
  sem_wait(&phil[id]);
}

void test(int id) {
  if (state[id] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
    state[id] = EATING; 
    sem_post(&phil[id]);
  }
}

int main() {
  pthread_t philosophers[NPHIL];
  int ids[NPHIL];
  
  sem_init(&mutex, 0, 1);
  
  for (int i=0; i<NPHIL; i++) {
    sem_init(&phil[i], 0, 1); 
    ids[i] = i;   
  }
  
  for (int i=0; i<NPHIL; i++) {
    pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
  }
  
  for (int i=0; i<NPHIL; i++) {
    pthread_join(philosophers[i], NULL);
  }
  
  for (int i=0; i<NPHIL; i++) {
    sem_destroy(&phil[i]);
  }
  
  sem_destroy(&mutex);
  return 0; 
}
