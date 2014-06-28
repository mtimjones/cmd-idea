// list.h -- list structures and function prototypes
//

#ifndef __LIST_H__
#define __LIST_H__

typedef struct link_s {
  struct link_s* next;
  struct link_s* prev;
} link_t;

typedef struct list_s {
  struct link_t* first;
  struct link_t* last;
} linked_list_t;

void listAdd( linked_list_t* list, link_t* item );


#endif // __LIST_H__
