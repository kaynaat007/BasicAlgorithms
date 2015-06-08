import java.util.*;


public class find_path extends DFS {
	
	
	static boolean flag = false;
	
	
	void dfs_visit_1 ( Map m , int i, int d ) {
		
		time = time  + 1;
		visited[i] = 1;
		start[i] = time;
		Vector v = new Vector();

		System.out.println ( "visiting : " + i ) ;		
		v = ( Vector) m.get(i);
		int x;
		for ( int j = 0 ; j < v.size(); j++) {
			
			  x = (int)v.get(j);
			  if ( x == d ) 
			  {
				  find_path.flag = true;
				  return;
				 
				  
			  }
			  if ( visited[x] == 0 ) { // x has not been visited. 
				  
				  parent[x] = i;
				  dfs_visit_1 ( m, x, d  );
		         					  
			  }
					
		}
		
		time  = time + 1;
		end[i] = time;
	    visited[i] = 2;
	   
   			
	}
	
	

	
	public static void main ( String [] args ) {
		
        find_path  f = new find_path() ;
        Scanner in  = new Scanner ( System.in  ) ;
        int source;
        int destination;
        int n;
        int i;
        int k;
        int x;
        
        Map m = new HashMap ();
        System.out.println ( "Enter the  number of vertices :  "  ) ;
      
        n = in.nextInt();
        
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
        f.init(n);
        f.print(m);
        System.out.println ( "enter source : ") ;
        source = in.nextInt();
        System.out.println ( "Enter destination : ") ;
        destination = in.nextInt();
        f.init(n);
        f.dfs_visit_1(m, source, destination) ;
        if ( flag ) {
        	System.out.println ( "path exist ") ;
        	
        }    // if 
        else {
        	
        	
        	System.out.println ( "path does not exist ") ;
        	
        } // else 
        
       		
	}
	

}
