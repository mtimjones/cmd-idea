// utils.c
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

unsigned int isCommonWord( char *word )
{
   const char *commonWords = 
      { "the be to of and a in that have I it for not on with he as you do "
        "at this but his by from they we say her she or an will my one all "
        "would there their what so up out if about who get which go "
        "me when make can like no just him know take into "
        "your some could them see other than then now only come "
        "its over also back after use two how our work well way even "
        "want because any these give most us" };

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

