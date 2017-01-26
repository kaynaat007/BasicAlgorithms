import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Vector;


public class BasicDFS {
	
	int time = 0; // time counter 
	int [] parent = new int[10]; // to store  parent of each vertex 
	int [] start = new int[10]; //  start[i] is time at which node i was first visited
	int [] end = new int[10] ; // end[i] is end time at which node i was fininshed 
	int [] visited = new int[10]; // to keep track which node got visited which not. 
	

void display ( Vector v ){ //  the list of vertices linked to each vertex. this prints them . 
		
		int i;
		for ( i = 0; i < v.size(); i++ ) {
			
		     System.out.print ( v.get(i) ) ;
		     System.out.print ( ' ') ;
		    			
		}
		
		System.out.println ( "end ") ;		
		
}
		
	
void print ( Map m ) { // to print the graph which is a HashMap
		
		int i;
		int x;
		int s;
		
		for  ( i = 0; i < m.size(); i++ ) {
			
			//s =   ( (int[]) m.get( i ) ).length ;
			Vector v = new Vector();
			 v =  (Vector) m.get(i) ; // get the vertices associated with vertex i 
			 display ( v ) ;
						
		}
		
	}
	
	
	
void display_array ( int []  v ){ // to print array we have declared globally. 
		
		int i;
		for ( i = 0; i < v.length; i++ ) {
			
		     System.out.print ( v[i] ) ;
		     System.out.print ( ' ') ;
		    			
		}
		
		System.out.println ( "end ") ;
		
		
	}
	
	

	
	
void init( int n ) { // to initialize all the arrays . 
		
		
	    int i;
	    for ( i = 0; i < n; i++) {
	       	
	    	parent[i] = -1; // parent of all nodes is -1 before dfs 
	    	start[i]  = -1; // start time for all nodes is -1 
	    	end[i]  = -1; // end time for all nodes is -1 
	    	visited[i] = 0;	 // all nodes are initially not visited, so marked white ( 0 ) . 
	    	
	    }
	  
	}
	
	
void dfs_visit ( Map m , int i ) { // the  function which actualy does dfs at vertex i 
		
		time = time  + 1; // visiting node i for first time, increment timer 
		visited[i] = 1; // mark node i as grey . now this node will be explored 
		start[i] = time; // store start time of this node 
		Vector v = new Vector(); // to collect vertices adjacent to this node i 
		v = ( Vector) m.get(i); // m is our adjaceny list representation of the graph . 
		int x;
		for ( int j = 0 ; j < v.size(); j++) {
			
			  x = (int)v.get(j);
			  if ( visited[x] == 0 ) { // if x has not been visited. 
				  
				  parent[x] = i; // x has parent i . 
				  dfs_visit ( m, x ); // then visit x. 
		         					  
			  }
					
		}
		
		time  = time + 1; // vertex i is done. increment timer.
		end[i] = time; // store finish time 
		visited[i] = 2; // mark node i as visited. 
			
	}
	
	void dfs (  Map m, int source  ) {
		
		int i;
		 // Vector is only to store vertices. first vertex which is source is pushed into the queue. 
		// remaining are pushed in order of index  i . 
	    Vector vertices = new Vector();
	    vertices.addElement((int)source);
	    for ( i = 0; i < m.size(); i++ ) {
	    	
	    	if( i != source ) {
	    		
	    		vertices.addElement( i);  
	    		
	    	}    	
	    }
	    
		
		 for  ( int k = 0; k <  vertices.size(); k++  )    {
			 
 		    i =  (int)vertices.get(k) ;
 		    System.out.println ( "vertex " + i + "is there") ;
 		    	   
 		    // if vertex i has not been visited, visit it. 
			if ( visited[ i] == 0 ) {
				
				dfs_visit ( m, i ) ;
				
			} // if 
	
		} // while
		   
		
	}

	 public static void main ( String [] args ) {
		   
		   int i;
		   int n;
		   int j;
		   int k;
		   Scanner in  = new Scanner  ( System.in) ;
		   System.out.println ( "enter the number of vertices : ") ;
		   n = in.nextInt();
		   int x ;
		   
		   Map m = new HashMap(); // a hasMap to store our graph. it has two fields. 
		   // key is vertex, and value is a vector of vertices connected to that vertex . 
		 
		   for ( i = 0; i < n; i++ ) {
		
			  Vector v = new Vector();
			  System.out.println ( "Enter vertex connected to this vertex : "  + i  ) ;
			  System.out.println ( "press -1 when done ") ;
			  k = 0;
			  while ( true) {
				  
				 x = in.nextInt();
				 if ( x == -1 )
					 break;
				 v.addElement(x);
				 k++;
				  			  
			  }
			  
			  m.put( i , v ) ;
			 		  		   
		   }
		   BasicDFS d = new BasicDFS();
		   
		   d.init(n); // intialize all  arrays 
		   d.print ( m ) ; // print the adjaceny list 
		   System.out.println ("enter the source vertex : ")  ;
		   int source  = in.nextInt(); 
		   d.dfs(m, source );  // run dfs on source 
		   d.display_array(d.visited); // print visited array 
		   d.display_array(d.start); // print start array 
		   d.display_array(d.end); // print end array 
		   d.display_array(d.parent); // print parent array . 
		   
				   
	 }
	
}




