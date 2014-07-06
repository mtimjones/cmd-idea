// dictionary.h
//

#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include "string.h"

#define MAX_WORD_SIZE	30

typedef struct d_entry {
  char word[ MAX_WORD_SIZE+1 ];
  int  count;
} d_entry;

void initDictionary( void );
void addWordToDictionary( char *word );
int findWordInDictionary( char *word );
void sortDictionary( void );
void printDictionary( int num );
void createDictionaryFromText( char* text );

#endif /* __DICTIONARY_H__ */
