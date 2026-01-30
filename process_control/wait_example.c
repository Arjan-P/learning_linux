/*
Macro Description
WIFEXITED(status) True if status was returned for a child that terminated normally. In this
case, we can execute
WEXITSTATUS(status)
to fetch the low-order 8 bits of the argument that the child passed to
exit, _exit, or _Exit.
WIFSIGNALED(status) True if status was returned for a child that terminated abnormally, by
receipt of a signal that it didn’t catch. In this case, we can execute
WTERMSIG(status)
to fetch the signal number that caused the termination.
Additionally, some implementations (but not the Single UNIX
Specification) define the macro
WCOREDUMP(status)
that returns true if a core file of the terminated process was generated.
WIFSTOPPED(status) True if status was returned for a child that is currently stopped. In this
case, we can execute
WSTOPSIG(status)
to fetch the signal number that caused the child to stop.
WIFCONTINUED(status) True if status was returned for a child that has been continued after a
job control stop (XSI option; waitpid only).
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void pr_exit(int status)
{
  if(WIFEXITED(status))
  
    // child exited normally through exit, _exit, or _Exit
    printf("normal process termination, status code: %d\n", WEXITSTATUS(status));
  
  else if (WIFSIGNALED(status))
    // child killed by signal
    // The process is dead
    // It did not call exit() or return from main
    // A signal killed it
    printf("abnormal termination, signal number: %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
                                  WCOREDUMP(status) ? " Core file generated" : "");
#else
           "");
#endif
  else if(WIFSTOPPED(status))
    // child stopped by signal
    printf("child stopped, signal number: %d\n", WSTOPSIG(status)); 
  
}

int main()
{
  pid_t pid;
  int status;

  if((pid = fork()) < 0)
    fprintf(stderr, "fork error");
  else if(pid == 0)
    // inside child process; exit normally
    exit(7);

  // in parent process
  if(wait(&status) != pid)  // blocking wait call
  {
    fprintf(stderr, "wait error");
  }
  pr_exit(status);

  if((pid = fork()) < 0)
    fprintf(stderr, "fork error");
  else if(pid == 0)
    // inside child process; generate abort signal
    abort();
  
  // in parent process
  if(wait(&status) != pid)  // blocking wait call
  {
    fprintf(stderr, "wait error");
  }
  pr_exit(status);

  if((pid = fork()) < 0)
    fprintf(stderr, "fork error");
  else if(pid == 0)
    // inside child process; division by zero
    status /= 0;

  // in parent process
  if(wait(&status) != pid)  // blocking wait call
  {
    fprintf(stderr, "wait error");
  }
  pr_exit(status);
  exit(0);
}
