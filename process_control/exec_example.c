#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// list of pointer to environment strings
char *env_init[] = {"USER=unknown", "PATH=/tmp", (char*)0};

int main()
{
  pid_t  pid;
  if((pid = fork()) < 0)
  {
    fprintf(stderr, "fork error");
    exit(1);
  }
  else if(pid == 0)
  {
    // child process
    if(execle("/usr/bin/echo", "echo", "arg1", "arg2", (char*)0, env_init) < 0)
    {
      fprintf(stderr, "execle error");
      exit(1);
    }
    // start new process in child process address space
  }

  // wait for child to terminate in parent process
  if(waitpid(pid, NULL, 0) != pid)
  {
    fprintf(stderr, "wait error");
    exit(1);
  }
  exit(0);
}
