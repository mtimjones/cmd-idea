// interp.c
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "ideadb.h"
#include "list.h"

int last_identifier = 0;

void execInterpreter( ideas_t* ideas )
{
   char *input, shell_prompt[6];

   snprintf( shell_prompt, sizeof(shell_prompt), "idea>" );

   while (1)
   {
      input = readline( shell_prompt );

      if (!input) continue;

      add_history( input );

      // Parse the command
      if ( !strncmp( input, "add", 3 ) )
      {
         char *idea_text = &input[3];

         while ( *idea_text == ' ' ) idea_text++;

         printf("Length %d, Idea: %s\n", strlen( idea_text ), idea_text );

         if ( strlen( idea_text ) > 0 )
         {
            idea* cur_idea = (idea *)calloc( 1, sizeof( idea ) );
            cur_idea->text = (char *)malloc( strlen( idea_text ) + 1 );
            strncpy( cur_idea->text, idea_text, strlen( idea_text ) );
            cur_idea->identifier = last_identifier++;
            listAdd( ideas, (link_t *)cur_idea );
         }

      }
      else if ( !strncmp( input, "list", 4 ) )
      {
         link_t* link = ideas->first;
         while (link)
         {
            printf("Idea: %s\n", ((idea *)link)->text);
            link = link->next;
         }

      }

      free( input );
   }

   return;
}

