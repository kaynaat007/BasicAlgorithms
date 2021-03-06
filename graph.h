#ifndef __GRAPH_H_INCLUDED__   // if x.h hasn't been included yet...
#define __GRAPH_H_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#define R 100
#define C 100

struct node {

	int dest;
	int weight;
	struct node * next;

};

struct adjList {
	struct node * head;

};

struct graph {
    int v;
    struct adjList * array;
};

struct node *  newAdjListNode( int dest, int weight ) {

	struct node * new_node = ( struct node * ) malloc( sizeof( struct node) );  // make a new node 
	new_node -> dest = dest;
	new_node -> next = NULL;
	new_node -> weight = weight;
	return new_node;

}

struct graph * make_graph ( int v ) {

	struct graph * g = ( struct graph * ) malloc ( sizeof( struct graph ) ); // make a graph node. 
	g -> v = v;
	g -> array = ( struct adjList * ) malloc ( v * sizeof ( struct adjList ) ); // make an array of adjList type nodes. This 
	int i;
	for ( i = 0 ; i < v; i++ ) {
		g -> array[i].head = NULL;
	}
	return g;

}

void addEdge ( struct graph * g, int src, int dest, int weight = 0) {
        // edge  from src to dest 
        //printf ("adding weight %d", weight);

	struct node * n =  newAdjListNode(dest, weight);
	n -> next = g -> array[src].head;
	g -> array[src].head = n;

	/*
        //  edge from dest to src 
	n = newAdjListNode ( src );
	n -> next = g -> array[dest].head;
	g -> array[dest].head = n;
	*/
}

void printGraph ( struct graph * g ) {
   int v;
   for ( v = 0; v < g -> v; v++ ) {
	   struct node  * crawl = g -> array[v].head;
	   printf ( "Adjacent list for this vertex %d ---> ", v );
	   while ( crawl ) {

		   printf ( "%d (%d)   ", crawl -> dest, crawl->weight);
		   crawl = crawl -> next ;

	   }
	   printf ( "\n" );

   }

}

void freemem( struct graph * g ) {

   int v;
   for ( v = 0; v < g -> v; v++ ) {
	   struct node  * crawl = g -> array[v].head;
	   free ( crawl );
   }

  free ( g );

}


#endif
