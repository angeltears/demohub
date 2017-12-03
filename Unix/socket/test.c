#include "connect.h"

int main(int argc, char *argv[])
{
  int sockfd = unblcok_connect(argv[1], atoi(argv[2]),10);
  if (sockfd < 0)
  {
    return 1;
  }
  close(sockfd);
  return 0;
}
