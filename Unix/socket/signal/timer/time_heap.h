#ifndef TIME_HEAP_H
#define TIME_HEAP_H

#include <iostream>
#include <time.h>
#include <netinet/in.h>
using std::exception;

#define BUFF_SIZE 64

class heap_time;

typedef struct client_data
{
  sockaddr_in addr;
  int sockfd;
  char buf[BUFF_SIZE];
  heap_time * timer;
}client_data;

class heap_time
{
public:
  heap_time(int delay)
  {
    expire = time(NULL) + delay;
  }
public:
  client_data *user_data;
  void (*cb_func)(client_data *);
  int expire;
};



class time_heap
{
public:
  time_heap(int capacity) throw(std::exception): capacity(capacity), cur_size(0)
  {
    array = new heap_time*[capacity];
    if (!array)
    {
      throw std::exception();
    }
    for (int i = 0; i < capacity; i++)
    {
      array[i] = NULL;
    }
  }
  time_heap(heap_time**init_array, int size, int capacity) throw(std::exception):capacity(capacity), cur_size(size)
  {
    if (capacity < size)
    {
      throw std::exception();
    }
    array = new heap_time*[capacity];
    if (!array)
    {
      throw std::exception();
    }
    for (int i = 0; i < capacity; i++)
    {
      array[i] = NULL;
    }
    if (size)
    {
      for (int i = 0; i < size; i++)
      {
        array[i] = init_array[i];
      }
      for(int i = 0; i < size; ++i)
      {
        perrolate_down(i);
      }
    }
  }
  ~time_heap()
  {
    for (int i = 0; i < cur_size; ++i)
    {
      delete array[i];
    }
    delete[] array;
  }

public:
  int add_timer(heap_time *timer) throw(std::exception);
  void del_timer(heap_time *timer);
  void pop_timer();
  heap_time* top() const;
  void tick();
  bool empty() const  {return cur_size == 0;}
  void adjust_down() { perrolate_down(0);}
private:
  void perrolate_down(int hole);
  void resize() throw (std::exception);

private:
  heap_time **array;           // 堆数组
  int capacity;                //　堆数组的容量
  int cur_size;                //　堆数组当前包含元素个数
};

int time_heap::add_timer(heap_time *timer) throw(std::exception)
{
  if (!timer)
  {
    return -1;
  }
  if (cur_size >= capacity)
  {
    resize();
  }
  int hole = cur_size++;
  int parent = 0;
  for ( ; hole > 0; hole = parent)
  {
    parent = (hole - 1) / 2;
    if (array[parent]->expire > array[hole]->expire)
    {
      break;
    }
    array[parent] = array[hole];
  }
  array[hole] = timer;
  std::cout<<"a new cli coming in "<<timer->user_data->sockfd<<std::endl;
  return 0;
}

void time_heap::del_timer(heap_time *timer)
{
  if (!timer)
  {
    return;
  }
  timer->cb_func = nullptr;
}

void time_heap::pop_timer()
{
  if(empty())
  {
    return;
  }
  if (array[0])
  {
    delete array[0];
    array[0] = array[cur_size--];
    perrolate_down(0);
  }
}

heap_time* time_heap::top() const
{
  if(empty())
  {
    return nullptr;
  }
  return array[0];
}

void time_heap::tick()
{
  std::cout<<"tick"<<std::endl;
  heap_time *tmp = array[0];
  time_t cur = time(NULL);
  while(!empty())
  {
    if(!tmp)
    {
      return;
    }
    if (tmp->expire > cur)
    {
      break;
    }
    if (array[0]->cb_func)
    {
      array[0]->cb_func(array[0]->user_data);
    }
    pop_timer();
    tmp = array[0];
  }
}

void time_heap::perrolate_down(int hole)
{
  heap_time *tmp = array[hole];
  int child = 0;
  for ( ;(hole * 2 + 1) < (cur_size - 1); hole = child)
  {
    child = hole * 2 + 1;
    if ((child < cur_size -1) && (array[child + 1] > array[child]))
    {
      ++child;
    }
    if (array[child] < array[hole])
    {
      array[hole] = array[child];
    }
    else
    {
      break;
    }
  }
  array[hole] = tmp;
}

void time_heap::resize() throw (std::exception)
{
  heap_time** tmp = new heap_time *[2 * capacity];
  if (!tmp)
  {
    throw std::exception();
  }
  for (int i = 0; i < capacity * 2; i++)
  {
    tmp[i] = NULL;
  }
  capacity = 2 * capacity;
  for (int i = 0; i < cur_size; i++)
  {
    tmp[i] = array[i];
  }
  delete []array;
  array = tmp;
}


#endif
