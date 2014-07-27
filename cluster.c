// cluster.c
// Simple implementation of k-means clustering.

#include <float.h>
#include <math.h>
#include <assert.h>
#include "ideadb.h"
#include "dictionary.h"

double *centroids[MAX_K];
int centroid_counts[MAX_K];

extern int verbose;

void assignRandomIdeaToCluster( ideas_t* ideas, int k, int c )
{
   int index, cur, i;
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
               ((idea *)link)->cluster = k;
               if (verbose) printf( "Cluster %d, starts with idea %d\n", k, index );
               for ( i = 0 ; i < c ; i++ )
               {
                  centroids[k][i] = (double)((idea *)link)->BoWVector[i];
               }
               return;
            }
         }

         cur++;
         link = link->next;
      }
   }

   return;
}


void kmeans_cluster_init( ideas_t* ideas, int k, int c )
{
   int i;

   assert( ideas );

   for (i = 0 ; i < k ; i++ )
   {
      centroids[i] = (double *)calloc( 1, (c*sizeof(double)) );
      centroid_counts[i] = 0;
   }

   for ( i = 0 ; i < k ; i++ )
   {
      assignRandomIdeaToCluster( ideas, i, c );
   }

   return;
}


void kmeans_cluster_destroy( int k )
{
   int i;

   for (i = 0 ; i < k ; i++ )
   {
      free( (void *)centroids[i] );
   }

   return;
}


void kmeansDetermineMembership( idea* idea, int k, int c )
{
   double min_distance = DBL_MAX;
   int i, j;

   for ( i = 0 ; i < k ; i++ )
   {
      double distance = 0;

      for ( j = 0 ; j < c ; j++ )
      {
         distance += pow( ((double)idea->BoWVector[j] - centroids[i][j] ), 2 );
      }

      if (verbose) printf("   Cluster %d distance %g\n", i, distance );

      if ( distance < min_distance )
      {
         idea->cluster = i;
         min_distance = distance;
      }

   }

   // Add the member to its cluster
   for ( j = 0 ; j < c ; j++ )
   {
      centroids[idea->cluster][j] += (double) idea->BoWVector[j];
   }

   // Increment the cluster counter
   centroid_counts[ idea->cluster ]++;

   return;
}


void recomputeCentroids( ideas_t* ideas, int k, int c )
{
   int i, j;
   link_t* link;

   for ( i = 0 ; i < k ; i++ )
   {
      centroid_counts[ i ] = 0;
      for ( j = 0 ; j < c ; j++ )
      {
         centroids[i][j] = 0.0;
      }
   }

   link = ideas->first;
   while ( link )
   {
      // Add the member to its cluster
      for ( j = 0 ; j < c ; j++ )
      {
         centroids[((idea*)link)->cluster][j] += (double) ((idea *)link)->BoWVector[j];
         centroid_counts[ ((idea*)link)->cluster ]++;
      }

      link = link->next;
   }

   // Update the Centroids based upon its members
   for ( i = 0 ; i < k ; i++ )
   {
      if (verbose) printf(" Centroid %d: ", i);
      for ( j = 0 ; j < c ; j++ )
      {
         centroids[i][j] /= (float)centroid_counts[i];
         if (verbose) printf( "%g ", centroids[i][j] );
      }
      if (verbose) printf("\n");
   }

   return;
}


void kmeans_iterate( ideas_t* ideas, int k, int c )
{
   link_t* link;
   int iterations = 200;

   do {

      link = ideas->first;

      // Assign members to centroids
      while ( link )
      {
         if (verbose) printf("Checking %d\n", ((idea*)link)->identifier );

         kmeansDetermineMembership( (idea*)link, k, c );

         link = link->next;
      }

      recomputeCentroids( ideas, k, c );

   } while (iterations--);

   return;
}


void kmeans( ideas_t* ideas, int k, int c )
{
   if (verbose) printf("k %d, c %d\n", k, c );

   // Create Cluster initial members
   kmeans_cluster_init( ideas, k, c );

   kmeans_iterate( ideas, k, c );

   kmeans_cluster_destroy( k );

   return;
}

