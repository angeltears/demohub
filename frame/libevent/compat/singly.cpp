#include <iostream>
#include "queue.h"

struct node
{
  int data;
  SLIST_ENTRY(node);
};

int main()
{
   SLIST_HEAD(list, node);
   struct list mylist;
   SLIST_INIT(&mylist);

   for (int i = 0; i < 5; i++)
   {
     struct node * s = new node;
     s->data = i;
     SLIST_INSERT_HEAD(s, list, node);
   }
	SLIST_FOREACH(s, list, node)
  {
    std::cout<<s->data<<std::endl;
  }
}
