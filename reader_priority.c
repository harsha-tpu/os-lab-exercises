#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rLock, wLock; // semaphores for controlling access
int n_reader = 0; // counter
int shared_data = 0; // shared resource

void *reader(void *arg) {
  int id = *(int *)arg; 
  
  sem_wait(&rLock); // locking other readers
  n_reader++;  // incrementing reader count
  if(n_reader ==  1) {
    sem_wait(&wLock);  
  }
  
  sem_post(&rLock);
  printf("Reader %d is reading the  shared data %d\n",  id, shared_data);
  sleep(1); 
  
  sem_post(&wLock); 
  return NULL;
}

void *writer(void *arg) {
  int id = *(int *)arg; 
  
  sem_wait(&wLock); // locking for writer
  
  shared_data++; 
  printf("Writer %d is writing shared data: %d\n", id, shared_data);
  sleep(1); 
  sem_post(&wLock); // unlocking the  writer
  
  return NULL;
}

int main() {
  pthread_t rId[5], wId[5];
  int reader_ids[5] = {1, 2, 3, 4, 5};
  int writer_ids[3] = {1, 2, 3};
  
  // initialize semaphores
  sem_init(&rLock, 0, 1);
  sem_init(&wLock, 0, 1);
  
  // create reader and writer threads
  for (int i=0; i<5; i++) {
    pthread_create(&rId[i], NULL, reader, &reader_ids[i]);
  }
  
  for (int i=0; i<3; i++) {
    pthread_create(&wId[i], NULL, writer, &writer_ids[i]);
  }
  
  // join threads (ensure they finish)
  for (int i=0; i<5; i++) {
    pthread_join(rId[i], NULL);
  }
   
  for (int i=0; i<3; i++) {
    pthread_join(wId[i], NULL);
  }
  
  // destroy semaphores
  sem_destroy(&rLock);
  sem_destroy(&wLock);  
}





