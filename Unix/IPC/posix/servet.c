#include "msg.h"

int main(int argc, char *argv[])
{
  key_t key = Ftok(argv[1],atoi(argv[2]));
  int msg_id = Megget(key, IPC_CREAT|IPC_EXCL|0755);

  MSG msg_ser;
  while (1)
  {
    printf("SER >");
    scanf("%s", mesg_ser.mesg_date);
    printf("\n");
    mesg.mesg_tpye = SER_SND;
    Msgsnd(msg_id, &mesg_ser, strlen(mesg_date)+1, 0);

    memset(&mesg, 0, sizeof(mesg));
    Msgrcv(msg_id, &mesg_ser, BUF_SIZE, SER_REC, 0);
    printf("CLI > %s\n", mesg_ser.mesg_tpye);
  }
  msgctl(msg_id, IPC_RMID, NULL);

}
