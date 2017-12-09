#ifndef TIME_WHEEL_H
#define TIME_WHEEL_H
#include <time.h>
#include <netinet/in.h>
#include <stdio.h>

#define BUFF_SIZE 64
class tw_timer;
typedef struct client_data
{
  sockaddr_in address;
  int sockfd;
  char buff[BUFF_SIZE];
  tw_timer *timer;
}client_data;

class tw_timer
{
public:
  tw_timer(int ra, int ts):prev(NULL), next(NULL),\
   roration(ra), time_slot(ts){};
public:
  int roration;              //记录定时器在时间轮多少圈后生效
  int time_slot;             //记录定时器属于时间轮上的那个槽
  void (*cb_func)(client_data *);
  client_data *user_data;
  tw_timer *prev;
  tw_timer *next;
};

class time_wheel
{
public:
  time_wheel():cur_slot(0)
  {
    for (int i = 0; i < N; ++i)
    {
      slots[i] = nullptr;
    }
  }
  ~time_wheel()
  {
    for (int i = 0; i < N; i++)
    {
      tw_timer *tmp = slots[i];
      while(tmp)
      {
        slots[i] = tmp->next;
        delete tmp;
        tmp = slots[i];
      }
    }
  }
  //根据定时器的timeout 创建一个定时器，并把它插到定时器中
  tw_timer* add_timer(int timeout);
  //删除目标定时器
  void del_timer(tw_timer *timer);
  //SI 时间到后，调整该函数，时间轮向前滚动一个槽的间隙
  void tick();
private:
  static const int N = 60;         //时间轮上的槽的数目
  static const time_t SI = 1;         //每１s时间轮转动一次，取槽的间隔为１s
  tw_timer *slots[N];             //时间轮的槽，其中，每个元素指向一个定时器的链表，链表无序
  int cur_slot;                   //时间轮当前槽数
};
tw_timer* time_wheel::add_timer(int timeout)
{
  if (timeout < 0)
  {
    return nullptr;
  }

  int tick = 0;
  if (timeout < SI)
  {
    tick = 1;
  }
  else
  {
    tick = timeout / SI;
  }

  int roration = tick / N;
  int ts = (cur_slot + (tick % N)) %N;
  tw_timer *timer = new tw_timer(roration, ts);

  if(!slots[ts])
  {
    printf("add timer, roration is %d, ts is %d, cur_slot is %d\n", roration, ts, cur_slot);
    slots[ts] = timer;
  }
  else
  {
    timer->next = slots[ts];
    slots[ts]->prev = timer;
    slots[ts] = timer;
  }
  return timer;
}

void time_wheel::del_timer(tw_timer *timer)
{
  if (!timer)
  {
    return;
  }
  int ts = timer->time_slot;

  if (timer == slots[ts])
  {
    slots[ts] = slots[ts]->next;
    if (slots[ts])
    {
      slots[ts]->prev = NULL;
    }
    delete timer;
  }
  else
  {
    timer->prev->next = timer->next;
    if (timer->next)
    {
      timer->next->prev = timer->prev;
    }
    delete timer;
  }
}

void time_wheel::tick()
{
  tw_timer *tmp = slots[cur_slot];
  printf("current slot is %d\n", cur_slot);
  while(tmp)
  {
    printf("tick the timer once\n");
    if (tmp->roration > 0)
    {
      tmp->roration--;
      tmp = tmp->next;
    }
    else
    {
      tmp->cb_func(tmp->user_data);
      if(tmp == slots[cur_slot])
      {
        slots[cur_slot] = tmp->next;
        delete tmp;
        tmp = slots[cur_slot];
      }
      else
      {
        tmp->prev->next = tmp->next;
        if (tmp->next)
        {
          tmp->next->prev = tmp->prev;
        }
        tw_timer *nxtmp = tmp->next;
        delete tmp;
        tmp = nxtmp;
      }
    }
  }
  cur_slot = ++cur_slot % N;
}
#endif
