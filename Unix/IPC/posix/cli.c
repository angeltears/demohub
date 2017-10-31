#include "msg.h"

int main(int argc, char *argv[])
{
  key_t key = Ftok(argv[1], atoi(argv[2]));
  int msg_id = Msgget(key, 0);

  MSG mesg;
  while(1)
  {
    Msgrcv(msg_id, &mesg, BUF_SIZE, CLI_REC, 0);
    printf("SER > %s", mesg.mesg_date);

    memset(&mesg, 0, sizeof(mesg));
    printf("CLI >");
    scanf("%s",mesg.mesg_date);
    mesg.mesg_tpye = CLI_SND;
    Msgsnd(msg_id, &mesg, strlen(mesg.mesg_date)+1, 0);
  }
  return 0;
}
