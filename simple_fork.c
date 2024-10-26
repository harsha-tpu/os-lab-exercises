#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Process PID: %d PPID %d\n", getpid(), getppid());
  int pid = fork();  // creating a child process
  if (pid != 0) { // parent
    printf("Parent Process PID: %d PPID: %d\n", getpid(), getppid());
    printf("Parent's child : %d\n", pid);
  } else { // child
    printf("Child Process PID: %d PPID: %d\n", getpid(), getppid());
  }
  return 0;
}
