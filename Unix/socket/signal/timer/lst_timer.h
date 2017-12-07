#ifndef LST_TIMER_H
#define LST_TIMER_H

#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#define BUFFER_SIZE 64

class util_time;
class sort_timer_list;

typedef struct client_data
{
  sockaddr_in sock;
  int sockfd;
  char buff[BUFFER_SIZE];
  util_time *time;
}client_data;

class util_time
{
public:
  util_time():prev(NULL), next(NULL){}
public:
  void (*cb_func)(client_data *);
  time_t expire;
  client_data *user_data;
  util_time *prev;
  util_time *next;
};

class sort_timer_list
{
public:
  sort_timer_list(): head(NULL), tail(NULL){}
  ~sort_timer_list()
  {
    util_time *tmp = head;
    while (tmp)
    {
      head = tmp->next;
      delete tmp;
      tmp = head;
    }
  }
  void add_timer(util_time *timer);
  void adjust_timer(util_time *timer);
  void del_timer(util_time *timer);
  void tick();
private:
  void add_timer(util_time *timer, util_time *lst_head);
  util_time *head;
  util_time *tail;
};

void sort_timer_list::add_timer(util_time *timer)
{
  if (!timer)
  {
    return;
  }
  if (!head)
  {
    head = tail = timer;
    return;
  }

  if(timer->expire < head->expire)
  {
    timer->next = head;
    head->prev = timer;
    head = timer;
    return;
  }
  add_timer(timer, head);
}

void sort_timer_list::add_timer(util_time *timer, util_time *lst_head)
{
    util_time *prev = lst_head;
    util_time *ptr = prev->next;
    while (ptr)
    {
      if (timer->expire < ptr->expire)
      {
        prev->next = timer;
        timer->prev = prev;
        ptr->prev = timer;
        timer->next = ptr;
        break;
      }
      prev = ptr;
      ptr = ptr->next;
    }

    if (!ptr)
    {
      prev->next = timer;
      timer->next = NULL;
      timer->prev = prev;
      tail = timer;
    }
}

void sort_timer_list::adjust_timer(util_time *timer)
{
  if (!timer)
  {
    return;
  }

  util_time *tmp = timer->next;
  if ( !tmp || (timer-> expire < tmp->expire))
  {
    return;
  }

  if (timer == head)
  {
    head = head->next;
    head->prev = NULL;
    timer->next = NULL;
    add_timer(timer, head);
  }
  else
  {
    timer->prev->next = timer->next;
    timer->next->prev = timer->prev;
    timer->next = NULL;
    timer->prev = NULL;
    add_timer(timer, head);
  }
}
void sort_timer_list::del_timer(util_time *timer)
{
  if (!timer)
  {
    return;
  }
  if ((timer == head) && (timer == tail))
  {
    delete timer;
    head = tail = NULL;
    return;
  }
  if (timer == head)
  {
    head = head->next;
    head->prev = NULL;
    delete timer;
    return;
  }
  if (timer == tail)
  {
    tail = timer->prev;
    tail->next = NULL;
    delete timer;
    return;
  }

  timer->prev->next = timer->next;
  timer->next->prev = timer->prev;
}

void sort_timer_list::tick()
{
  if(!head)
  {
    return;
  }
  printf("timer tick\n");
  time_t cur = time(NULL);
  util_time *tmp = head;
  while (!tmp)
  {
    if (cur < tmp->expire)
    {
      break;
    }

    tmp->cb_func(tmp->user_data);
    head = tmp->next;
    if (head)
    {
      head->prev = NULL;
    }
    delete tmp;
    tmp = head;
  }
}

#endif
