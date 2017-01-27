
#include "graph.h"
#include "advanced_heap.h"

#include <iostream>
#include <cstdio>
#include<climits>

#define MAX 1000

using namespace std;


int edgeTo[MAX];
int distTo[MAX];

void relax ( int u, int v, int weight, struct MinHeap * heap ) {
       
	 if (  distTo[u] + weight < distTo[v] ) {

               // distTo[v] is reduced ! 
               distTo[v] = distTo[u] + weight;
	       // set new found path to v through u
	       edgeTo[v] = u;

	       if ( !isInMinHeap ( heap, v) )  {
		       // if v is not in heap, insert v with new distTo[v] 
		       insertMinHeap ( heap, v, distTo[v] ); 
	       }
	       else { 
		       // decrease priority of v to distTo[v] 
		       decreaseKey(heap, v, distTo[v] );
	       }

	 }
}



void dijkstra(struct graph * my_graph, int source) {
      
	int i;
	int vertices = my_graph -> v;
	int u;
	int v;
	int weight;
	struct MinHeap * heap = createMinHeap(vertices);
	int tree[vertices];

	for ( i = 0; i < vertices; i++ ) {
		 distTo[i] = INT_MAX; // every vertex is at INFINITE DISTANCE apart from source vertex
		 edgeTo[i] = -1; // every vertex edgeTo value is NULL.
		 tree[i] = -1;
	}

	insertMinHeap(heap, source, 0); // insert source vertex with priority zero 
	distTo[source] = 0;

	while ( !isEmpty(heap) ) {

                // extract and delete this vertex from the heap 
		struct MinHeapNode * node = extractMin(heap);
		u = node -> element;
		struct node * crawl = my_graph -> array[u].head;
		while ( crawl ) {
                        v = crawl -> dest;
			// relax edge (u, v). 
			relax (u, v, crawl -> weight, heap);
			crawl = crawl -> next;
		}
	}
}


void printShortedDistanceVertexArray(int v) {

	int i;
	for ( i = 0; i < v; i++ )
		printf ( "%d --> (%d) \n", i, distTo[i] );
}
int main(){

	int vertices;
	int edges;
	int i;
	int source;
	int destination;
	int weight;

	scanf ( "%d", &vertices);
	scanf ( "%d", &edges);

	struct graph * my_graph = make_graph(vertices);

	for ( i = 0; i < edges; i++ ) {
		scanf ( "%d", &source);
		scanf ( "%d", &destination);
		scanf ( "%d", &weight);

		addEdge(my_graph, source, destination, weight);
	}
	printGraph(my_graph);
	dijkstra(my_graph, 0);
	printShortedDistanceVertexArray(my_graph->v);


return 0;
}
