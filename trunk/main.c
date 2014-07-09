// main.c
//

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "ideadb.h"

int verbose = 0;
int term_width;

ideas_t ideas;

void displayHelp( void )
{
   return;
}

int main ( int argc, char* argv[] )
{
   int c;
   char *db_dir;
   struct winsize w;

   ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );
   term_width = w.ws_col;

   db_dir = getenv( "HOME" );

   while (( c = getopt( argc, argv, "hvd:")) != -1 )
   {
      switch( c )
      {
         case 'v':
            verbose = 1;
            break;
         case 'h':
            displayHelp( );
            return 0;
         case 'd':
            {
               DIR* dir = opendir( optarg );
               if ( dir )
               {
                  db_dir = optarg;
                  closedir( dir );
               }
               else if ( errno == ENOENT )
               {
                 printf("Specified subdirectory does not exist.\n");
                 return 0;
               }
            }
            break;
         default:
            printf( "Unknown option %c\n", (char)c );
            break;
      }
   }

   if (verbose)
   {
      printf("Using directory %s\n", db_dir);
   }

   listInit( &ideas );

   // Try to read the idea database into the list
//   readDatabase( &ideas, db_dir );

   execInterpreter( &ideas );

//   storeDatabase( &ideas, db_dir );

   return 0;
}

