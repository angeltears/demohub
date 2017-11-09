#include <stdio.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <unistd.h>
static void sig_usr(int);

int main()
{
  if((signal(SIGUSR1, sig_usr)) == SIG_ERR)
  {
    printf("can't catch SIGUSR1\n");
  }
  if((signal(SIGUSR2, sig_usr)) == SIG_ERR)
  {
    printf("can't catch SIGUSR2\n");
  }
  while(1)
  {
    pause();
  }
}

static void sig_usr(int signo)
{
  if (signo == SIGUSR1)
  {
    printf("recive  SIGUSR1\n");
  }
  if (signo == SIGUSR2)
  {
    printf("recive SIGUSR2\n");
  }
  else
  {
    printf("recive error SIGNAL %d\n", signo);
    exit(1);
  }
}
