#include"knn.h"

//constructor
/*
name: knn
desc: allocates a 2d array of doubles. 
params: int num_cols
returns: void
1) allocate a double array pointer IMPORTANT_SIZE length
2) for each element of the double array allocate an array of _num_cols length
*/
knn::knn( int num_cols )
  : _num_cols(num_cols)
{
  int i; 
  
  // make new 2D important vector array
  // of our selected important size 
  _important = new double*[_IMPORTANT_SIZE] ;// allocate rows
  assert( _important); 
  // last element will be its category

  for( i=0; i<_IMPORTANT_SIZE; i++)
    assert( _important[i] = new double[_num_cols] ); //allocate 
}

//desctructor
/*
name: ~knn
desc: deletes each element of the _important vector array..then deletes the
important array. 
params: n/a
returns: n/a
1) delete [] each array pointed to by the _important[x] array
2) delete [] the _important array
*/
knn::~knn()
{
 int i; 
   for( i=0; i<_IMPORTANT_SIZE; i++) 
     delete [] _important[i];// delete column array 
 
   delete [] _important; 
}

/*
name: find_important
desc: randomly selects and stores important vectors from the train data set.
 Making sure it doesn't select the same row twice. 
params: data_set * traind
returns: void
1) for each element of the _important vector array do steps 2-8		(L)
2) while we don't have a valid vector selection do steps 3-6		(L)
3) generate a random intiger between 0 and IMPORTANT_SIZE
4) check to make sure we have generated and stored that row before. 
5) if it has then generate a new one. 
6) once we have a valid number store it in our used_row array
7) copy the data from that the random row train row into the next available
   row of our _important vector array
8) in the last element of each _important vector array store the outcome. 
*/
void knn::find_important(data_set * train)// finds important vectors 
{
 int i,k,j,once=0, random;
  row  * temp_row; 
  int  used_rows[_IMPORTANT_SIZE]; 
  int  valid;
  int curr_size=0; 
 
  for( i=0; i<_IMPORTANT_SIZE; i++)// size of random important vectors
  {
    valid = 0;
    while( valid == 0 ) // make sure we don't select the same row 
    {
      random = rand() % train->get_num_rows(); // pull random important vectors

      for( j=0; j<curr_size; j++)//loop through checking to see if its been used
	if(random != used_rows[j] )// if it is a new number
	  valid++;// if any bad number it will make it invalid

      for(once=once; once<1; once++)//first time the number is valid. 
	  valid++ ;
    }
    used_rows[curr_size] = random; // store which valid row we just found
    curr_size ++;   //add one to current used_row size; 
  
    temp_row = train->get_row( random );// pull out the random tow from train 
    // store the elements in our important set
    for(k=0; k<_num_cols-1; k++)// object doesn't store outcome in array
      _important[i][k] = temp_row->get_col_data( k ); 
     
    // store outcome in last element ( _num_cols element)
    _important[i][k] =  temp_row->get_outcome();  
  }
}

/*
name: sort_important
desc:  sorts the rows in our _important array according to the geometric 
distance of the row given and the current  row of _important array. 
params: row * r
returns: void 
0) while the number_switched != 0 do steps 1-4				(L)
1) for each element of the _important array do steps 2-	4		(L)
2) calculate the geometric distance between the row and that element of		
   important. 	 	   	    	    	    	     	     	(F)
3) calculate the geometric distance between the row and that element +1 of
   important 	 	   	    	    	    	     	     	
4) if the second distane is greater then the first distance then switch the
   rows and add one to the number_switched. 
*/ 
// sorts the important vectors in closest to farthest order
void knn::sort_important( row * r )
{
  int i, number_switched=1; // get into loop first time 
  double distance1, distance2; 
  double * temp_row; 
  
  // implement MERGE SORT... as many as needed times 
  //if we loop through the whole thing without having to switch any it is sorted
   while( number_switched != 0 )
   {
     number_switched = 0; // initialize howmany switched first 
     for( i=0; i<(_IMPORTANT_SIZE-1); i++)
     {
       distance1 = get_dist( r->get_row_data(), _important[i] ); 
       // get distance1
       distance2 = get_dist( r->get_row_data(), _important[i+1]); 
       // get distance2
              
       // if distance2 is greater then distance1 then switch the rows 
       if( distance2 < distance1 )
       {
	 temp_row = _important[i]; 
	 _important[i] = _important[i+1]; 
	 _important[i+1] = temp_row; 
	 
	 number_switched ++ ; 
       }
     }
     // end of while loop 
   }
}


// Step 2 of sort_important
/*
name: get_dist
params: double * train, double test 
desc: calculates the sum of the geometric distances between each given array
params: double * traind, double * test
returns: double
1) for each column of the arrays do step 2				(L)
2)    temp += pow( (train[i] - test[i]), 2); 
3) take the square root of the temp 
4) return distance. 
*/
// finds the geometric distance between train vector and test vector
double knn::get_dist( double * train , double * test )
{
  int i;
  double temp=0;
  double distance=0; 

  for(i=0; i<_num_cols-1; i ++)
    temp += pow( (train[i] - test[i]), 2); /* square it */ 

  distance = sqrt(temp); 
  return distance; 
}

/*
name: classify_row
desc: classifies the row by the average of the first _k outcomes
params: int kVal
returns: int
1) for the first kVal rows of _important sum up the outcomes		(L)
2) if the outcomes are greater then 0  return 1
3) if the outcomes are less then 0 return -1
4) generate a random number between 1 and 2
5) if random is 2 return 1
6) else return -1. //note this should only be neccessary with even k values
*/ 
int knn::classify_row(int kVal) 
{
  int outcomes=0; 
  int i; 
  int random; 

  for( i=0; i<kVal; i++)
    outcomes += _important[i][_num_cols-1] ; // sum up the neighbours outcomes
   
  // last element of _important array is the outcome 
  if(outcomes > 0 )
    return 1; 

  if( outcomes < 0 )
    return -1; 

  // else then they must be equal....randomly pick between categories
  // note: this only will possibly  happen if _k is an even number
  random = rand() % 2 + 1; // make 1 or 2
 
  if( random == 2 )
    return 1; 
  else 
    return -1;
}

/* 
name: print
desc: prints the _important array
params: noe
returns: void
*/ 
void knn::print( )
{
  int i, j;
  
  for( i=0; i<_IMPORTANT_SIZE; i++)
  {
    for( j=0; j<_num_cols; j++)
      cout<<_important[i][j]<<" ";
    
    cout<<endl; 
  }

}
