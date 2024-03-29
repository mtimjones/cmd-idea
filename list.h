// list.h -- list structures and function prototypes
//

#ifndef __LIST_H__
#define __LIST_H__

typedef struct link_s {
  struct link_s* next;
  struct link_s* prev;
} link_t;

typedef struct linked_list_t {
  link_t* first;
  link_t* last;
} linked_list_t;

typedef void (*iter_callback_t)( link_t * link );

void listInit( linked_list_t* list );
void listAdd( linked_list_t* list, link_t* item );
void listIterate( linked_list_t* list, iter_callback_t callback );

#endif // __LIST_H__
