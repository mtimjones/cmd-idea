// dictionary.c
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dictionary.h"
#include "utils.h"

#define MAX_WORDS	1000

d_entry dictionary[ MAX_WORDS ];
int     last_entry;

void initDictionary( void )
{
   int i;

   last_entry = 0;

   for ( i = 0 ; i < MAX_WORDS ; i++ )
   {
      dictionary[i].word[0] = 0;
      dictionary[i].count = 0;
   }

   return;
}


void addWordToDictionary( char *word )
{
   int i;

   i = findWordInDictionary( word );

   if ( i == MAX_WORDS )
   {
      // Add to the end
      assert( last_entry < MAX_WORDS );
      i = last_entry++;
      strncpy( dictionary[ i ].word, word, MAX_WORD_SIZE );
   }

   dictionary[ i ].count++;

   return;
}


int findWordInDictionary( char *word )
{
   int i;

   for ( i = 0 ; i < last_entry ; i++ )
   {
      if ( dictionary[ i ].count )
      {
         if ( strlen( dictionary[ i ].word ) != strlen( word ) ) continue;
         if ( !strncmp( dictionary[ i ].word, word, strlen( word ) ) )
         {
            return i;
         }
      }
   }

   return MAX_WORDS;
}


void sortDictionary( void )
{
   int i;
   int swapped = 1;
   d_entry temp_word;

   if (last_entry < 2) return;

   while ( swapped )
   {
      swapped = 0;

      for ( i = 0 ; i < last_entry-2 ; i++ )
      {
         if ( dictionary[ i+1 ].count == 0 ) break;

         if ( dictionary[ i ].count < dictionary[ i+1 ].count )
         {
            memcpy( (void *)&temp_word, (void *)&dictionary[ i ], 
                     sizeof( d_entry ) );
            memcpy( (void *)&dictionary[ i ], (void *)&dictionary[ i + 1],
                     sizeof( d_entry ) );
            memcpy( (void *)&dictionary[ i+1 ], (void *)&temp_word,
                     sizeof( d_entry ) );

            swapped = 1;
         }
      }
   }

   return;
}


void printDictionary( int num )
{
   int i;
   int max = num;

   if (max > last_entry) max = last_entry;

   for ( i = 0 ; i < max ; i++ )
   {
      printf("%02d (%03d): %s\n", i, dictionary[i].count, dictionary[i].word );
   }
   printf("\n");

   return;
}


void createDictionaryFromText( char* text )
{
   char *token;
   const char *delim=".,;? {}()!@#$%^&*";
   char *copy;

   copy = (char *)malloc( strlen( text ) + 1 );
   strcpy ( copy, text );
   convertToLowercase( copy );

   token = strtok( copy, delim );

   while ( token != NULL )
   {
      addWordToDictionary( token );

      token = strtok( NULL, delim );
   }

   free( copy );

   return;
}
