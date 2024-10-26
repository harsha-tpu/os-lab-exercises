#include <stdio.h>
#include <unistd.h>

int main() {
  int p[2]; 
  char inbuf[10], outbuf[10]; 
  if (pipe(p) == -1) {
    printf("Pipe not created\n");
    return 1;
  } else {
    int pid = fork();
    if (pid) {
      printf("Parent Process | Enter data: ");
      scanf("%s", outbuf);
      write(p[1], outbuf, sizeof(outbuf));
    } else {
      read(p[0], inbuf, sizeof(inbuf));
      printf("Child Process | Data Received: %s\n", inbuf);    
    }
  }
  return 0; 
}
