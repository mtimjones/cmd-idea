// cluster.c
// Simple implementation of k-means clustering.

#include <stdlib.h>
#include <stdio.h>
#include "ideadb.h"
#include "dictionary.h"

#define getSRand()      ((float)rand() / (float)RAND_MAX)
#define getRand(x)      (int)((x) * getSRand())

void assignRandomIdeaToCluster( ideas_t* ideas, int c )
{
   int index, cur;
   link_t* link;

   extern int last_identifier;

   while ( 1 )
   {
      index = getRand( last_identifier );
      link = ideas->first;
      cur = 0;

      while ( link )
      {
         if ( cur == index )
         {
            if ( ((idea *)link)->cluster == -1 )
            {
               ((idea *)link)->cluster = c;
               printf( "Cluster %d, starts with idea %d\n", c, index );
               return;
            }
         }

         cur++;
         link = link->next;
      }
   }

   return;
}


void kmeans_cluster_init( ideas_t* ideas, int k )
{
   int c;

   for ( c = 0 ; c < k ; c++ )
   {
      assignRandomIdeaToCluster( ideas, c );
   }

   return;
}


void kmeans( ideas_t* ideas, int k )
{

   // Create Cluster initial members
   kmeans_cluster_init( ideas, k );



   return;
}

