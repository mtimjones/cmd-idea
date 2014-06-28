// ideadb.h -- Idea database structures
//

#ifndef __IDEADB_H__
#define __IDEADB_H__

#include "list.h"

typedef struct idea {
  link_t* link;

  char* text;
  
} idea;

#endif // __IDEADB_H__
