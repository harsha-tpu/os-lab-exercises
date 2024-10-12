#include <stdio.h>

int empty = 5;
int full = 0;
int s = 1; // semaphore var

void wait(int *s){
  (*s)--;
}

void signal(int *s){
  (*s)++;
}

void producer(int buffer[]){
  if(empty <= 0){
    printf("buffer is full");
    return;
  }
  
  wait(&empty);
  wait(&s);
  printf("Enter a item to produce: ");
  scanf("%d", &buffer[full]);
  signal(&s);
  signal(&full);
}

void consumer(int buffer[]){
  if(full <= 0){
    printf("buffer is empty\n");
    return;
  }
  
  wait(&full);
  wait(&s);
  printf("%d is consumed\n", buffer[full]);
  signal(&s);
  signal(&empty);
}

int main(){
  int buffer[5];
  int ch;
  do {
    printf("1.Produce | 2.Consume | 3.Exit\n");
    scanf("%d", &ch);
    switch(ch){
      case 1:
        producer(buffer);
        break;
      case 2: 
        consumer(buffer);
        break;  
      default: 
        break;
    }
  } while (ch != 3);
  return 0;
}
