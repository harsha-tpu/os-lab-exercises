#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Process PID: %d PPID %d\n", getpid(), getppid());
  int pid = fork(); // creating a child 
  if (pid != 0) {
    printf("Parent Process PID: %d PPID: %d\n", getpid(), getppid());
    printf("Parent's child is %d\n", pid);
  } else {
    sleep(5);
    printf("Child Process PID: %d PPID: %d\n", getpid(), getppid());
  }
  printf("PID %d terminates\n", getpid()); // Both process executes this 
  return 0; 
}
