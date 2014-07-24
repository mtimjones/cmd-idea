// ideadb.h -- Idea database structures
//

#ifndef __IDEADB_H__
#define __IDEADB_H__

#include "list.h"
#include "time.h"

#define IDEA_DB_FILE ".ideadb"

typedef linked_list_t ideas_t;

typedef struct idea {
  link_t link;
  char*  text;
  unsigned int identifier;
  char*  addedDate;
  int    cluster;
  unsigned char* BoWVector;
} idea;

void execInterpreter( ideas_t* );

#endif // __IDEADB_H__
