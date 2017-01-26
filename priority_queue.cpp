#include <cstdio>
#include <iostream>
#include<climits>

using namespace std;

int left_child( int i ) {

	return 2 * i + 1; // 0 based indexing 
}

int right_child ( int i ) {
        
	return 2 * i + 2;  
}

int parent ( int i ) {

  if ( i == 0 )
     return -1;
  if ( i%2 == 0 )
  	return i/2 - 1;

  return i/2; 

}


int min_two ( int arr[], int i, int j ) {
    if ( i == j )
	    return i;
    if ( arr[i] < arr[j] )
	    return i;
    return j;
}

int three_min( int arr[], int i, int j, int k) {

	int min_index = min_two(arr, i, j );

	if ( arr[k] < arr[min_index] )
		return k;

        return min_index;
}

void swap( int arr[], int i, int j ) {
	
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;

}

void heapify ( int arr[], int i, int n ) {
	
	int left_child_index = left_child(i);
	int right_child_index = right_child(i);
	int min_index;
        // return if index i has no left and right child 
	if (left_child_index >= n && right_child_index >= n )
		return ;
        // find min index if both children are present 
	if ( left_child_index < n  && right_child_index < n )
		 min_index = three_min(arr, i, left_child_index, right_child_index); // the min index of three indexes
        // find min index if only left child is present
	else if ( left_child_index < n ) {

		 min_index = min_two(arr, i, left_child_index);
//	         printf ( "%d\n", min_index);

	}
	// this case won't occur but whatever. 
        else
		min_index = min_two(arr, i, right_child_index);

       // swap i with min_index and recurse. 
	if ( min_index != i ) {
		swap(arr, i, min_index);
		heapify(arr, min_index, n);
	}
}


void decrease_key(int arr[], int i, int n, int key) {

	int par;
	int par_value;

	if ( i >= n )
		return; 

	if ( key >= arr[i] )
		return;

	arr[i] = key; // set key to i 

	while ( 1 ) {
		 par = parent(i); // get parent of i 
		 if ( par == -1 )
			 break;
		 par_value = arr[par]; // get the value of parent 

		 if ( par_value <=  arr[i] )
			 break;

		 swap(arr, par, i );
		 i = par;
	}
}
void build_heap( int arr[], int n ) {
   int p  =  n/2 - 1;
   int i;
   for ( i = p; i >=0; i-- ) {
	
	   heapify( arr, i, n);
   }
}

void printHeap( int arr[], int n ) {
  
   int i;
   for ( i = 0; i < n; i++ ) 
	   printf ( "%d ", arr[i] );

   printf ( "\n" );
}

void delete_min(int arr[], int *n) {

	if ( n  < 0 )
		return; 
	swap (arr, 0, (*n)-1);
	*n = *n - 1; 
	heapify(arr, 0, *n);
}

int main() {

	int arr[100];
	int n;
	int y;
	int i;
	int j;
	int key;

	scanf( "%d", &n);

        for ( i = 0; i < n;  i++ )
		scanf("%d", &arr[i]);

	build_heap( arr, n );
	printHeap( arr, n );
       
	delete_min(arr, &n);
	printHeap(arr, n);

	delete_min(arr, &n);
	printHeap(arr, n);

	delete_min(arr, &n);
	printHeap(arr, n);

        /* 
	scanf ( "%d", &y);

	for ( i = 0; i < y; i++ ) {
		scanf ( "%d", &j);
		scanf ( "%d", &key);
		decrease_key(arr, j, n, key);
		printHeap( arr, n);
		printf ( "\n" );
	}
	*/

return 0;
}
