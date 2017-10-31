#include "msg.h"

int main(int argc, char *argv[])
{
  key_t key = Ftok(argv[1], atoi(argv[2]));
  int msg_id = Msgget(key, 0);

  struct mesg mesgs;
  while(1)
  {
    Msgrcv(msg_id, &mesgs, BUF_SIZE, CLI_REC, 0);
    printf("SER > %s\n", mesgs.mesg_date);

    memset(&mesgs, 0, sizeof(mesgs));
    printf("CLI >");
    scanf("%s",mesgs.mesg_date);
    mesgs.mesg_tpye = CLI_SND;
    Msgsnd(msg_id, &mesgs, strlen(mesgs.mesg_date)+1, 0);
  }
  return 0;
}
