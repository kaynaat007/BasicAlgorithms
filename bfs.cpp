#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<climits>
#include<queue>
#define R 105
#define C 105
#define INF INT_MAX

using namespace std;


struct node {

	int dest;
	struct node * next;

};

struct adjList {
	struct node * head;

};

struct graph {
    int v;
    struct adjList * array;
};

struct node *  newAdjListNode( int dest ) {

	struct node * new_node = ( struct node * ) malloc( sizeof( struct node) );  // make a new node 
	new_node -> dest = dest;
	new_node -> next = NULL;
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

void addEdge ( struct graph * g, int src, int dest ) {
        // edge  from src to dest 
	struct node * n =  newAdjListNode( dest );
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

		   printf ( "%d   ", crawl -> dest );
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



void do_bfs( struct graph * g, int source, int visited[], int distance[] , char arr[]  ) {

	int v = g -> v;
	int e;
	int i;
	int to;
	queue<int>q;
	q.push(source);
	distance[source] = 0;
	visited[source] = 1;

	while ( !q.empty() ) {

		e = q.front();
		q.pop();
		if ( arr[e] == '#')
			continue;

		struct node * crawl = g -> array[e].head;
		while ( crawl != NULL ) {

			to = crawl -> dest;

			if ( visited[to] == -1 && arr[to] != '#') {
				visited[to] = 1;
				distance[to] = distance[e] + 1;
				q.push(to);
			}
			crawl = crawl -> next;
		}

	}

}



void add_edges ( struct graph * g, char G[][C],  int r, int c,  char arr[] ) {

	  int  k = 0;
	  int i;
	  int j;
          for ( i = 0; i < r; i++ ) {
		for ( j = 0; j < c; j++ ) {


			if ( i == 0 && j == 0 ) {   
				    addEdge(g, k, k+1);
				    addEdge(g, k, k+ c );
			}
			else if ( i == 0 && j == c-1 ) {
				    addEdge(g, k, k-1);
				    addEdge(g, k, k + c );
			}
			else if ( i == r - 1 && j == 0 ) {
				    addEdge(g, k, k - c);
				    addEdge(g, k, k + 1 );

			}
			else if ( i == r - 1 && j == c - 1 ) {
				    addEdge(g, k, k - c );
				    addEdge(g, k, k - 1  );
			}
			else if ( i == 0 && j > 0 && j < c-1 ) {
				    addEdge(g, k, k - 1 );
				    addEdge(g, k, k + 1 );
				    addEdge(g, k, k + c  );
			}
			else if ( j == 0 && i > 0 && i < r - 1 ) {
				    addEdge(g, k, k + 1);
				    addEdge(g, k, k - c );
				    addEdge(g, k, k + c );				
			}
			else if ( i == r - 1 && j > 0 && j < c - 1 ) {
				    addEdge(g, k, k + 1 );
				    addEdge(g, k, k - 1 );
				    addEdge(g, k, k - c  );
			}
			else if ( j == c - 1 && i > 0 && i < r - 1 ) {
				    addEdge(g, k, k - 1);
				    addEdge(g, k, k + c );    
				    addEdge(g, k, k - c );				
			}
			else {    
				    addEdge(g, k, k - 1);
				    addEdge(g, k, k + 1);
				    addEdge(g, k, k + c );
				    addEdge(g, k, k - c );				
			}

			k = k + 1;
		     }
		}
	}
//	


int main() {

	int v;
	int m;
	int r;
	int c;
	int i;
	char G[R][C];
	int k;
	char arr[R*C+1];
	int j;
	int source;
	int visited[R*C];
	int distance[R*C];
	int shops[R*C];
	int f;
	int w;


	scanf ( "%d", &m);
	for ( w = 0; w < m; w++ ) {
		scanf ( "%d", &r);
		scanf ( "%d", &c);
		v = r * c;
		struct graph*  g = make_graph(v);
		g -> v = v;
		k = 0;
		for ( i = 0; i < r; i++ )
			scanf ( "%s", G[i] );

		for ( i = 0; i < r; i++ ) {
			for ( j = 0; j < c; j++ ) {
				arr[k] = G[i][j];
				visited[k] = -1;
				distance[k] = INF;
				if ( G[i][j] == 'C' )
					source = k;
				k = k + 1;

			}
		}

        add_edges(g, G, r, c, arr);
	do_bfs(g, source, visited, distance, arr);
	int max = 0;
	int sum = 0;
	int count = 0;

	for ( f = 0; f < r * c; f++ )  {
		if ( arr[f] == 'S' ) {
			if ( distance[f] > max ) 
				max = distance[f];
			count++;
			sum = sum + distance[f];
		}
	}
	sum = sum - max;
	sum = 2 * sum;
	sum = sum + max;
	sum = sum + count * 60;
	printf ( "%d\n", sum );
	
	freemem(g);

   }  


return 0;
}





