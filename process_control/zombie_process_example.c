#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;

  if((pid = fork()) < 0)
  {
    fprintf(stderr, "fork error");
    exit(1);
  }
  else if (pid == 0) {
    // first child
    if((pid = fork()) < 0)
    {
      fprintf(stderr, "fork error");
      exit(1);
    }
    else if (pid > 0) {
      // if second child created 
      printf("first child exit\n");
      exit(0);
    }
    // second child
    sleep(2);
    // parent process now init: pid 1
    printf("second child, ppid: %ld, pid: %ld exit\n", (unsigned long)getppid(), (unsigned long)getpid());
    exit(0);
  }
  if(waitpid(pid, NULL, 0) != pid)
  {
    fprintf(stderr, "wait error");
  }

  // orignial parent process can continue with execution knowing it is not parent of second child
  printf("parent exit\n");
  exit(0);
}
