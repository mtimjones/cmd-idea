// eyeoh.h -- File I/O
//

#ifndef __EYEOH_H__
#define __EYEOH_H__

#include <stdio.h>

// Read the database from an input file
void readDatabase( ideas_t *ideas, char *db_dir );

// Write the database to an output file
void storeDatabase( ideas_t *ideas, char *db_dir );

#endif // __EYEOH_H__
