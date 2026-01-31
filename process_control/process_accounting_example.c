#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
  pid_t pid;
  if((pid = fork()) < 0)
  {
    fprintf(stderr, "fork error");
    exit(1);
  }
  else if(pid == 0)
  {
    if(execl("/usr/bin/sh", "sh", "-c", "date", (char*)0) < 0)
    {
      fprintf(stderr, "execl error");
      exit(1);
    }
    exit(0);
  }
  if(waitpid(pid, NULL, 0) != pid)
  {
    fprintf(stderr, "wait error");
  }
  exit(0);
}
