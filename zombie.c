#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  int pid = fork(); 
  if (pid != 0) {
    while(1); // Never terminates
    sleep(100); 
  } else {
    exit(42); // Exit with a silly value 
  }
  return 0; 
}
