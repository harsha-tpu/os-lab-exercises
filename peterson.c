#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

/* Shared variables for simulation for Peterson algorithm */
/* flag: to indicate if a process is ready to enter its critical section */
/* turn: to indicate whose turn it is to enter its critical section */
bool flag[2] = {false, false}; 
int turn = 0; 

void *peterson(void *arg) {
  int id = *(int *)arg;
  int other = 1 - id; 
  
  flag[id] = true; 
  turn = other; 
  while (flag[other] && turn == other);
  printf("Process %d is in Critical section \n", id);
  sleep(1); 
    
  flag[id] = false; 
  printf("Process %d is in Remainder section \n", id);
  sleep(1); 
    
  return NULL; 
}


int main() {
  pthread_t t1, t2; 
  int id1 = 0, id2 = 1; 
  
  pthread_create(&t1, NULL, peterson, &id1); 
  pthread_create(&t2, NULL, peterson, &id2);
  
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
   
  return 0; 
}
