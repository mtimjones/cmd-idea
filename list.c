// list.c -- list helper functions.
//

#include "list.h"

void listAdd( linked_list_t* list, link_t* item )
{
  assert(list);
  assert(item);

  item->next = item->prev = NULL;

  if (list->last)
  {
    // Non-empty list, item added to the tail
    list->last->next = item;
    item->prev = list->last;
    list->last = item;
  }
  else
  {
    // Empty list, single item added
    list->first = item;
    list->last = item;
  }

  return;
}


void iterateList( linked_list_t* list, void* callback )
{
  link_t* link;

  assert(list);

  for (link = list->first ; link ; link = link->next) {
    callback( (link_t*)link );
  }

  return;
}

