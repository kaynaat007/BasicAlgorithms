import java.awt.List;
import java.util.*;

public class DFS {
	
	int time = 0;
	int [] parent = new int[10]; // to store parent of each node 
	int [] start = new int[10]; // to store starting time of each vertex 
	int [] end = new int[10] ; // to store ending time  of each vertex 
	int [] visited = new int[10]; // to say if ith node is visited or not . 
	
	void dfs (  Map m, int source  ) { // main dfs 
		
		int i;
		 // Vector is only to store vertices. first vertex which is source is pushed into the vector 
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
		   
		    	   
		    // if vertex i has not been visited, visit it. 
			if ( visited[ i] == 0 ) {
				
				dfs_visit_1 ( m, i ) ;
				
			} // if 
	
		} // while
		
	}
	
	void dfs_visit_1 ( Map m , int i ) { // called by main dfs 
		
		time = time  + 1;
		visited[i] = 1;
		start[i] = time;
		Vector v = new Vector();
		v = ( Vector) m.get(i);
		int x;
		for ( int j = 0 ; j < v.size(); j++) {
			
			  x = (int)v.get(j);
			  if ( visited[x] == 0 ) { // x has not been visited. 
				  
				  parent[x] = i;
				  dfs_visit_1 ( m, x );
		         					  
			  }
					
		}
		
		time  = time + 1;
		end[i] = time;
		visited[i] = 2;
			
	}
	
	
	void dfs_visit_2 ( Map m , int i ) { // called by transpose_dfs .
		
		
		time = time  + 1;
		visited[i] = 1;
		start[i] = time;
		
		Vector v = new Vector();
		
		System.out.print (i);
		System.out.print (' ');
		
		v = ( Vector) m.get(i);
		
		int x;
		for ( int j = 0 ; j < v.size(); j++) {
			
			  x = (int)v.get(j);
			  if ( visited[x] == 0 ) { // x has not been visited. 
				  
				  parent[x] = i;
				  dfs_visit_2 ( m, x );
		         					  
			  }
					
		}
		
		
		time  = time + 1;
		end[i] = time;
		visited[i] = 2;
		
			
	}

	void init( int n ) {
		
		
	    int i;
	    for ( i = 0; i < n; i++) {
	    	
	    	
	    	parent[i] = -1;
	    	start[i]  = -1;
	    	end[i]  = -1;
	    	visited[i] = 0;	
	    	
	    }
	  
	}
	void display ( Vector v ){
		
		int i;
		for ( i = 0; i < v.size(); i++ ) {
			
		     System.out.print ( v.get(i) ) ;
		     System.out.print ( ' ') ;
		    			
		}
		
		System.out.println ( "end ") ;
		
		
	}
	
	
void display_array ( int []  v ){ // to print array 
		
		int i;
		for ( i = 0; i < v.length; i++ ) {
			
		     System.out.print ( v[i] ) ;
		     System.out.print ( ' ') ;
		    			
		}
		
		System.out.println ( "end ") ;
		
		
	}
	
	void print ( Map m ) { // print the graph 
		
		int i;
		int x;
		int s;
		
		for  ( i = 0; i < m.size(); i++ ) {
			
			//s =   ( (int[]) m.get( i ) ).length ;
			Vector v = new Vector();
			 v =  (Vector) m.get(i) ;
			 display ( v ) ;
						
		}
		
	}
	
	
	
	Map transpose ( Map m) {  // transposes the graph m 
		
		int i ;
		int x;
		Map g = new HashMap ();
		for ( i = 0; i  < m.size(); i++ ) { // intialize the new graph with key and value  as a vector 
 			
			Vector w = new Vector();
			g.put(i, w);
						
		}
		for ( i = 0; i < m.size(); i++ ) {
			
			Vector v = new Vector();
			
			v = (Vector)m.get(i); // get all vertices for vertex i 
			
			for ( int  j = 0; j < v.size(); j++) {
				
				 x =  (int) v.get(j) ;
				 ((Vector)g.get(x)).addElement(i);
				 
			} // for 
						
		} // for 
		
	  print (g );
	  return g;
	  
	}
	
	ArrayList<Integer>  get_vertices(int n ) {  // sort the vertices according to finishing times  
		
		Map m =  new HashMap ();
		int i;
		for ( i = 0;i < n; i++  ){
			
			m.put( i, end[i] ) ;
						
		}
		
	ArrayList<Integer>arr = new ArrayList<Integer>(   m.keySet() );
	
	Collections.sort(arr, new Comparator<Integer>(){

		@Override
		public int compare(Integer o1, Integer o2) {
			// TODO Auto-generated method stub
			
			 return  end[o2] - end[o1] ;
		}
		
	});

	return arr;
    		  		
	}
	
	void transpose_dfs  ( Map m ) { // this function calls dfs_visit on transpose of the graph . 
		
		
	   ArrayList <Integer> arr = new ArrayList<Integer> () ;
	   arr  = get_vertices ( m.size() ) ; // this has vertices sorted in decreasing order of finishing times.
	   Iterator itr = arr.iterator();
       int k = 0;
       int x;
       
       init( m.size() ) ;  // reinitialize arrays .
       
	   while ( itr.hasNext() ) {
		   
		   x = (int)itr.next();
		   if ( visited[ x ] == 0     )   {
			   
			   System.out.println ( "Connected component : " + k );
			   dfs_visit_2 ( m,  x ) ;
			   k++ ;
			   	   		   	   			   
		   }// if 
		   
		   System.out.print('\n');
		 
		   	  		   
	   } // 
	  	   					
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
	   
	   Map m = new HashMap();
	 
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
	   DFS d = new DFS(); 
	   
	   d.init(n); // set all arrays 
	   d.print ( m ) ; // print the graph 
	   System.out.println ("enter the source vertex : ")  ;
	   int source  = in.nextInt(); // get the source from user 
	   d.dfs(m, source );  // run dfs on source 
	   d.display_array(d.visited); // display all arrays 
	   d.display_array(d.start);
	   d.display_array(d.end);
	   d.display_array(d.parent);
	   Map g  = d.transpose(m); // transpose the the graph m 
	   d.transpose_dfs(g); // run dfs on transposed graph g 
	   
	
	  	 	  	   	  	 		 
   }
	

}
