#include "msg.h"

int main(int argc, char *argv[])
{
  key_t key = Ftok(argv[1],atoi(argv[2]));
  int msg_id = Msgget(key, IPC_CREAT|IPC_EXCL|0755);

  struct mesg msgs;
  while (1)
  {
    printf("SER >");
    scanf("%s", msgs.mesg_date);
    msgs.mesg_tpye = SER_SND;
    Msgsnd(msg_id, &msgs, strlen(msgs.mesg_date)+1, 0);

    memset(&msgs, 0, sizeof(msgs));
    Msgrcv(msg_id, &msgs, BUF_SIZE, SER_REC, 0);
    printf("CLI > %s\n", msgs.mesg_date);
  }
  msgctl(msg_id, IPC_RMID, NULL);
  
}
