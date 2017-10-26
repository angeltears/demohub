#include <unistd.h>
#include <sys/stat.h>
#include <error.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
int main(int argc, char const *argv[]) {
  int fd[2];
  char buff[7];
  struct stat info;

  if (argc != 2)
  {
    perror("usage : test1 <pathname>");
  }
  mkfifo(argv[1], 0755);
  fd[0] = open(argv[1], O_RDONLY | O_NONBLOCK);
  fd[1] = open(argv[1], O_WRONLY | O_NONBLOCK);

  fstat(fd[0], &info);
  printf("fd[0] : st_size = %ld\n",(long) info.st_size);
  fstat(fd[1], &info);
  printf("fd[1] : st_size = %ld\n",(long) info.st_size);
  write(fd[1], buff, sizeof(buff));
  fstat(fd[0], &info);
  printf("fd[0] : st_size = %ld\n",(long) info.st_size);
  fstat(fd[1], &info);
  printf("fd[1] : st_size = %ld\n",(long) info.st_size);
  exit(0);
}
