// eyeoh.c -- File I/O
//

#include "ideadb.h"
#include "eyeoh.h"
#include <assert.h>
#include <string.h>

void readDatabase( ideas_t *ideas, char *db_dir )
{
   FILE* fp;
   idea* cur_idea;
   char filename[100];
   char text[256];
   int  identifier;
   char date[100];
   int  cluster;

   extern idea *createIdea( char *text, char *date );
   extern int last_identifier;

   sprintf(filename, "%s/%s", db_dir, IDEA_DB_FILE );

   fp = fopen( filename, "r" );

   if (!fp)
   {
      printf( "Unable to open database (%s).\n", filename );
      return;
   }

   while ( !feof( fp ) )
   {
      fgets( text, 100, fp );
      if ( feof( fp ) ) break;
      identifier = atoi( text );

      fgets( text, 100, fp );
      if ( feof( fp ) ) break;
      cluster = atoi( text );

      if ( feof( fp ) ) break;
      (void)fgets( date, 100, fp );
      date[ strlen(date) - 1 ] = 0;

      if ( feof( fp ) ) break;
      (void)fgets( text, 255, fp );
      text[ strlen(text) - 1 ] = 0;

      cur_idea = createIdea( text, date );
      assert( cur_idea );
      cur_idea->identifier = identifier;
      cur_idea->cluster = cluster;

      listAdd( ideas, (link_t *)cur_idea );

      if (identifier > last_identifier) last_identifier = identifier+1;
   }

   fclose( fp );

   return;
}

void storeDatabase( ideas_t *ideas, char *db_dir )
{
   link_t* link;
   FILE* fp;
   char filename[100];

   sprintf(filename, "%s/%s", db_dir, IDEA_DB_FILE );

   fp = fopen( filename, "w" );

   link = ideas->first;

   while ( link )
   {
      fprintf( fp, "%d\n", ((idea *)link)->identifier );
      fprintf( fp, "%d\n", ((idea *)link)->cluster );
      fprintf( fp, "%s\n", ((idea *)link)->addedDate );
      fprintf( fp, "%s\n", ((idea *)link)->text );

      link = link->next;
   }

   fclose( fp );

   return;
}
