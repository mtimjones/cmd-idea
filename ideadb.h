// ideadb.h -- Idea database structures
//

#ifndef __IDEADB_H__
#define __IDEADB_H__

#include <stdio.h>
#include <stdlib.h>

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

#define MAX_K	20

#define getSRand()      ((float)rand() / (float)RAND_MAX)
#define getRand(x)      (int)((x) * getSRand())

#endif // __IDEADB_H__
