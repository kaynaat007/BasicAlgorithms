#ifndef __ADVANCED_HEAP_H_INCLUDED__   // if x.h hasn't been included yet...
#define __ADVANCED_HEAP_H_INCLUDED__

#include<cstdio>
#include<cstdlib>
#include<climits>


struct MinHeapNode {

	int element;
	int priority;
};

struct MinHeap {

	int current_size;
	int capacity;
	int * current_position;
	struct MinHeapNode ** array; // basically an array for storing MinHeapNodes of heap 

};

// create a new MinHeapNode
struct MinHeapNode * createNewMinHeapNode( int element, int priority) {

	struct MinHeapNode * minHeapNode = ( struct MinHeapNode * ) malloc ( sizeof ( struct MinHeapNode ) );
	minHeapNode -> element = element;
	minHeapNode -> priority = priority;
	return minHeapNode;
}

// create a MinHeap with current size as 0 
struct MinHeap * createMinHeap ( int capacity ) {

	struct MinHeap * minHeap = ( struct MinHeap * ) malloc ( sizeof ( struct MinHeap ) );
	minHeap -> current_size = 0;
	minHeap -> capacity = capacity;
	minHeap -> current_position = ( int * ) malloc ( capacity * sizeof(int) ); // an array to store element -> index mapping. 
	int i;
	for ( i = 0; i < capacity; i++ )
		minHeap -> current_position[i] = INT_MAX;

	minHeap -> array = ( struct MinHeapNode ** ) malloc ( capacity * sizeof ( struct MinHeapNode * ) ); // array where
	// pointers to actual heap nodes exists. 
	return minHeap;

}

// swap two MinHeapNodes. 
void swapMinHeapNodes ( struct MinHeapNode ** n1, struct MinHeapNode ** n2 ) {
    
	 struct MinHeapNode * t = *n1;
	 *n1 = *n2;
	 *n2 = t;
}


int left_child ( int index ) {

	return 2 * index + 1;
}

int right_child ( int index ) {
 
       return 2 * index + 2;
}

int get_parent ( int index ) {
        
	if ( index == 0 )
		return -1; 

	return ( index - 1 ) / 2;
}

void minHeapify ( struct MinHeap * heap, int index ) {

        // get the left child index 
	int left_child_index = left_child ( index );
	// get the right child index 
	int right_child_index = right_child ( index );
	// get the current size 
	int current_size = heap -> current_size;
	int smallest = index;
  
	if ( left_child_index < current_size && heap -> array[left_child_index]->priority < heap -> array[smallest]->priority )
	           smallest =  left_child_index; 
	if ( right_child_index < current_size && heap -> array[right_child_index]->priority < heap -> array[smallest]->priority)
	  	   smallest = right_child_index;

        if ( smallest != index ) {

		MinHeapNode * smallestNode = heap -> array[smallest];
		MinHeapNode * currentNode = heap -> array[index];

		// set position of smallest node to 'index'
		// set position of index node to 'smallest' 
		heap -> current_position[smallestNode->element] = index;
		heap -> current_position[currentNode->element] = smallest;

		// swap nodes 
		swapMinHeapNodes( &heap->array[smallest], &heap->array[index] );

		minHeapify( heap, smallest);
	}

}



void decreaseKey( struct MinHeap * minHeap, int target_element, int target_priority ) {

        // get the index of target element 
	int target_element_index = minHeap -> current_position[target_element];

	// get the node and update it's dist value 
	struct MinHeapNode * target_node = minHeap -> array[ target_element_index];

	// check if the new priority is lesser then current priority or not 
	if ( target_priority >= target_node -> priority )
		return;
	target_node -> priority = target_priority;

	// now travel up to fix if any other node up has priority lesser than the current priority 
	int parent_index = get_parent( target_element_index );

	while ( parent_index != -1 && minHeap -> array[parent_index] -> priority > minHeap -> array[ target_element_index]->priority ) {
              
	      // set the index of parent to be of target_element_index
	      minHeap -> current_position[ minHeap -> array[parent_index] -> element ] = target_element_index;
	      // set the index of target element to be of parent 
	      minHeap -> current_position[ minHeap -> array[target_element_index] -> element ] = parent_index;
	      // swap the two pointers
              swapMinHeapNodes( &minHeap -> array[parent_index], &minHeap -> array[target_element_index]);
              // now the target_index will be parent index 
	      target_element_index = parent_index;
	      // new parent index will be parent of previous parent index 
	      parent_index = get_parent(parent_index);

	}
}

int  isInMinHeap ( struct MinHeap * minHeap, int element ) {
	if (  minHeap -> current_position [ element ] < minHeap -> current_size )
		return 1;
	return 0;
}

bool isEmpty ( struct MinHeap * minHeap ) {
	   return minHeap -> current_size == 0;
}

void insertMinHeap( struct MinHeap * minHeap, int element, int priority ) {

	struct MinHeapNode * node = createNewMinHeapNode(element, INT_MAX);

	// set the new index of this element
	minHeap -> current_position[element] = minHeap -> current_size;

	// set this node to array of pointers
	minHeap -> array[minHeap -> current_size] = node;

	// increase the size 
	minHeap -> current_size += 1;

	// decrease the priority of this element to priority
	decreaseKey(minHeap, element, priority);

}

struct MinHeapNode * extractMin ( struct MinHeap * heap ) {
        // fetch the root node 
	struct MinHeapNode * root = heap -> array [ 0 ];
	// fetch the last node 
	struct MinHeapNode * lastNode = heap -> array [ heap -> current_size - 1 ];
	// set root to lastNode 
        heap -> array [0] = lastNode;

	// update the position of last node 
	heap -> current_position [ lastNode -> element ] = 0;
	// update the position of root node. it's discarded now 
	heap -> current_position [root->element] = heap -> current_size - 1;
        // reduce the size by 1 
	heap -> current_size -= 1;
	// heapify root 
        minHeapify(heap, 0);

	return root;
}

void printHeap ( struct MinHeap * heap ) {

	int i;
	for ( i = 0; i < heap -> current_size; i++ ) {
 		printf ( "%d  %d\n", heap->array[i]->element, heap->array[i]->priority);
		
	}
	printf ( "\n" );
}

void printSortedElements ( struct MinHeap * heap ) {

       int i;
       int heap_size = heap -> current_size;
       for ( i = 0; i < heap_size; i++ ) {

            struct MinHeapNode * node = extractMin( heap );
	    printf ( "%d %d \n", node -> element, node -> priority );
       }
}

#endif

/*
int main(){

	int v;
	int i;
	int element;
	int priority;

	scanf ( "%d", &v);
	struct MinHeap * minHeap = createMinHeap(v);

	for ( i = 0; i < v; i++ ) {
		scanf ( "%d", &element);
		scanf ( "%d", &priority);
		insertMinHeap( minHeap, element, priority);
	}
	printHeap ( minHeap );
	printSortedElements ( minHeap );
	
return 0;
}

*/

