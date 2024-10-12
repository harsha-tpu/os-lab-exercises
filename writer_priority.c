#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rlock, wlock; 
int n_readers = 0; 
int shared_data = 0; 
int n_wait = 0; 

void *reader(void *arg) {
  int id = *(int *)arg; 
  
  sem_wait(&rlock); // locks other reader
  while(n_wait > 0) { // check if a writer is waiting
    sem_post(&rlock); // release it's lock
    usleep(100); // wait before checking
    sem_wait(&rlock); // try to acquire lock again
  }
  
  n_readers++; 
  if(n_readers == 1) {
    sem_wait(&wlock); // if it's the first reader, lock the writer
  }
  sem_post(&rlock); // unlock other reader
  
  printf("Reader %d is writing the shared data: %d\n", id, shared_data);
  sleep(1); 
  
  sem_wait(&rlock); // locks other readers
  n_readers--;
  if(n_readers == 0) {
    sem_post(&wlock); // if it's the last reader, unlock the writer
  }
  
  sem_post(&rlock); // unlock it's lock
  return NULL;
}

void *writer(void *arg) {
  int id = *(int *)arg; 
  
  sem_wait(&rlock); // locks other reader to signal waiting writer
  n_wait++; 
  sem_post(&rlock);
  
  sem_wait(&wlock); // acquires writing lock
  shared_data++;  
  printf("Writer %d is writing the shared data: %d\n", id, shared_data);
  sleep(1); 
  sem_post(&wlock); // unlocks the writing lock
  
  sem_wait(&rlock); 
  n_wait--; 
  sem_post(&rlock);
  
  return NULL;
}

int main() {
  pthread_t rId[5], wId[3];
  int reader_ids[5] = {1, 2, 3, 4, 5};
  int writer_ids[3] = {1, 2, 3};
  
  // initialize semaphores
  sem_init(&rlock, 0, 1);
  sem_init(&wlock, 0, 1);
  
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
  sem_destroy(&rlock);
  sem_destroy(&wlock); 
}
