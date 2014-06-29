// ideadb.h -- Idea database structures
//

#ifndef __IDEADB_H__
#define __IDEADB_H__

#include "list.h"

#define IDEA_DB_FILE ".ideadb"

typedef linked_list_t ideas_t;

typedef struct idea {
  link_t* link;
  char* text;
} idea;

void execInterpreter( ideas_t* );

#endif // __IDEADB_H__
