#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>
#include <errno.h>
#include <stdlib.h>

static jmp_buf jmpbuff;

static void sig_alrm(int signo);
unsigned int sleep2(unsigned int seconds);
static void sig_init(int);

int main()
{
  unsigned int unslept;
  if (signal(SIGINT, sig_init) == SIG_ERR)
  {
    perror("signal(SIGINT) error");
  }
  unslept = sleep2(5);
  printf("sleep2 retrun: %u\n",unslept);
  exit(0);
}

static void sig_alrm(int signo)
{
  longjmp(jmpbuff, 1);
}

unsigned int sleep2(unsigned int seconds)
{
  if (signal(SIGALRM, sig_alrm) == SIG_ERR)
  {
    perror("signal(SIGALRM) error");
  }

  if (setjmp(jmpbuff) == 0)
  {
    alarm(seconds);
    pause();
  }

  return(alarm(0));
}

static void sig_init(int signo)
{
  int i, j;
  volatile int k;

  printf("\nsig_int starting\n");
  for(i = 0; i < 300000; i++)
  {
    for(j = 0; i < 4000; j++)
    {
      k += i + j;
    }
  }

  printf("sig_int finished\n");
}
