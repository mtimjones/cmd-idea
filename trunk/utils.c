// utils.c
//

#include <stdio.h>
#include <ctype.h>
#define _GNU_SOURCE
#include <string.h>

unsigned int isCommonWord( char *word )
{
   const char *commonWords = 
      { " the be to of and a in that have i it for not on with he as you do "
        "at this but his by from they we say her she or an will my one all "
        "would there their what so up out if about who get which go simple "
        "me when make can like no just him know take into something build "
        "your some could them see other than then now only come better such "
        "its over also back after use two how our work well way even "
        "want because any these give most us " };

   char *location;

   location = strcasestr( commonWords, word );

   if ( location ) return 1;

   return 0;
}


void convertToLowercase( char *string )
{
   int i;

   for ( i = 0 ; i < strlen( string ) ; i++ )
   {
      if ( isupper( string[i] ) )
      {
         string[i] = tolower( string[i] );
      }
   }

   return;
}

