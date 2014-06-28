// main.c
//

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "ideadb.h"

void displayHelp( void )
{
   return;
}

int main ( int argc, char* argv[] )
{
   int c;
   char *home_dir;

   home_dir = getenv( "HOME" );

   printf( "home directory %s\n", home_dir );

   while (( c = getopt( argc, argv, "h")) != -1 )
   {
      switch( c )
      {
         case 'h':
            displayHelp( );
            return 0;
         default:
            printf( "Unknown option %c\n", (char)c );

      }
   }

   return 0;
}

