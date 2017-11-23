#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

static void sig_child(int);

int main()
{
  pid_t pid;

  if(signal(SIGCLD, sig_child) == SIG_ERR)
  {
    perror("signal error");
  }

  if ((pid = fork()) < 0)
  {
    perror("fork error");
  }
  else if (pid == 0)
  {
    sleep(2);
    _exit(0);
  }

  pause();
  exit(0);
}

static void sig_child(int signo)
{
  pid_t pid;
  int status;

  printf("SIGCLD received\n");

  if (signal(SIGCLD, sig_child) == SIG_ERR)
  {
    perror("signal error");
  }

  if ((pid = wait(&status)) < 0)
  {
    perror("wait error");
  }

  printf("pid = %d\n",pid);
}
