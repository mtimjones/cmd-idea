// interp.c
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "ideadb.h"
#include "list.h"
#include "utils.h"
#include "dictionary.h"

int last_identifier = 0;

void helpCommand( void )
{
   printf("\n");
   printf("Command         Description\n");
   printf("--------------  --------------------------------------------\n");
   printf("add <string>    Add a new idea to the database\n");
   printf("del <id>        Delete an idea from the database\n");
   printf("list            List all ideas in the database\n");
   printf("organize        Organize the ideas into clusters\n");
   printf("similar <id>    List similar ideas to defined idea\n");
   printf("search <words>  List ideas that contain the defined words\n");
   printf("topics          Identify the top 10 most common topics\n");
   printf("help            Show this help menu\n");
   
   printf("exit            Exit the application\n");
   printf("\n");
   return;
}


void searchCommand( ideas_t* ideas, char* input )
{
   char terms[10][40];
   int num_terms = 0;
   char cmd_line[256];
   char *token;
   char *delim = " ,";

   /* Grab the search terms */
   strcpy( cmd_line, &input[7] );

   token = strtok( cmd_line, delim );
   
   while ( token != NULL )
   {
      strcpy( terms[num_terms], token );
      num_terms++;
      token = strtok( NULL, delim );
   }

   
   if ( num_terms > 0 )
   {
      link_t* link = ideas->first;
      int i;

      while (link)
      {
         for ( i = 0 ; i < num_terms ; i++ )
         {
            if ( strstr( (const char *)((idea *)link)->text, terms[i] ) == 0 ) break;
         }

         if ( i == num_terms )
         {
            printf( "%4d: %s\n", ((idea *)link)->identifier, 
                                 ((idea *)link)->text );
         }

         link = link->next;
      }
   }

   return;
}

void addCommand( ideas_t* ideas, char *input )
{
   char *idea_text = &input[3];

   while ( *idea_text == ' ' ) idea_text++;

   if ( strlen( idea_text ) > 0 )
   {
      idea* cur_idea;
      char* date;
      time_t rawtime;

      cur_idea = (idea *)calloc( 1, sizeof( idea ) );

      cur_idea->text = (char *)malloc( strlen( idea_text ) + 1 );
      strncpy( cur_idea->text, idea_text, strlen( idea_text ) );

      cur_idea->identifier = last_identifier++;

      time( &rawtime );
      date = ctime( &rawtime );
      cur_idea->addedDate = (char *)malloc( strlen( date ) + 1 );
      strcpy( cur_idea->addedDate, date );
      cur_idea->addedDate[ strlen(cur_idea->addedDate)-1 ] = 0;

      listAdd( ideas, (link_t *)cur_idea );
   }

   printf("\n");

   return;
}


void listCommand( ideas_t* ideas )
{
   link_t* link = ideas->first;
   while (link)
   {
      printf("%4d: %s\n", ((idea *)link)->identifier, ((idea *)link)->text);
      link = link->next;
   }

   printf("\n");

   return;
}


void insertIdeaIntoDictionary( link_t* link )
{
   createDictionaryFromText( ((idea *)link)->text );
}


void topicsCommand( ideas_t* ideas )
{
   initDictionary( );

   listIterate( ideas, insertIdeaIntoDictionary );

   sortDictionary( );

   printDictionaryTopics( 10 );

   return;
}


void organizeCommand( ideas_t* ideas )
{
   initDictionary( );

   listIterate( ideas, insertIdeaIntoDictionary );

   printDictionary( 500 );

   return;
}


void execInterpreter( ideas_t* ideas )
{
   char *input, shell_prompt[6];
   int  running = 1;

   snprintf( shell_prompt, sizeof(shell_prompt), "idea> " );

   while ( running )
   {
      input = readline( shell_prompt );

      if (!input) continue;

      add_history( input );

      // Parse the command
      if ( !strncmp( input, "help", 4 ) )
      {
         helpCommand( );
      }
      else if ( !strncmp( input, "add", 3 ) )
      {
         addCommand( ideas, input );
      }
      else if ( !strncmp( input, "list", 4 ) )
      {
         listCommand( ideas );
      }
      else if ( !strncmp( input, "topics", 6 ) )
      {
         topicsCommand( ideas );
      }
      else if ( !strncmp( input, "organize", 8 ) )
      {
         organizeCommand( ideas );
      }
      else if ( !strncmp( input, "search", 5 ) )
      {
         searchCommand( ideas, input );
      }
      else if ( !strncmp( input, "exit", 4 ) )
      {
         running = 0;
      }

      free( input );
   }

   return;
}

