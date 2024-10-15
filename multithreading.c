#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>

void *calcPrime(void *arg) {
  int n = *(int *)arg; 
  int prime = true; 
  for (int i=2; i<=n/2; i++) {
    if (n%i == 0) {
      prime = false; 
    }
  }
  if (prime) {
    printf("%d is a prime number\n", n);
  }
  else {
    printf("%d is not a prime number\n", n);
  }
  return NULL; 
}

void *armstrong(void *arg) {
  int n = *(int *)arg; 
  int temp = n; 
  int digit = 0, result = 0; 
  while(temp != 0) {
    temp /= 10;
    digit++; 
  }
  temp = n; 
  while (temp != 0) {
    int r = temp % 10; 
    result += pow(r, digit);
    temp /= 10; 
  }
  
  if (n == result) {
    printf("%d is an armstrong number\n", n);
  } else {
    printf("%d is not an armstrong number\n", n);
  }
  return NULL; 
}

void *factorial(void *arg) {
  int n = *(int *) arg;
  long int result = 1;
  for (int i=1; i<=n; i++) {
    result *= i;
  }
  printf("Factorial of %d is %ld\n", n, result);
  return NULL;
}


int main() {
  int n;
  pthread_t threads[3];
  printf("Enter a number: ");
  scanf("%d", &n);
  
  pthread_create(&threads[0], NULL, &calcPrime, &n);
  pthread_create(&threads[1], NULL, &armstrong, &n);
  pthread_create(&threads[2], NULL, &factorial, &n);
  
  for (int i=0; i<3; i++) {
    pthread_join(threads[i], NULL);
  }
  
  return 0; 
}
