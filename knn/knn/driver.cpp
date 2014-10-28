#include "driver.h"
#include<stdio.h>
#include<stdlib.h>
// access 2d array by array[row][col]
driver::driver(char * train, char * test, int kVal)
  : _train(train), _test(test), _k(kVal) 
{
  int i; 

  check_valid_input();//make sure user input is valid

  _num_cols  = _train.get_num_cols(); 
  
  // make new 2D important vector array
// of our selected important size 
  _important = new double*[_IMPORTANT_SIZE];// allocate rows
  // last element will be its category
  assert(_important); 

  for( i=0; i<_IMPORTANT_SIZE; i++)
    assert( _important[i] = new double[_num_cols] ); //allocate cols

  find_important();// randomly selects important vectors for this run 
}

driver::~driver()
{
  int i; 
  for( i=0; i<_IMPORTANT_SIZE; i++) 
    delete  [] _important[i];// delete column array 
 
  delete [] _important; 
}

void driver::calc_outcome()
{
  int i; 
  double truth, guess;
  row * r;
  int errors = 0; 
  double accuracy;

  for ( i = 0; i < _test.get_num_rows(); i ++ )
  {
    r = _test.get_row(i);
   
    sort_important( r ); // sorts important vectors accoring to this test vector
   
    guess = classify_row( );// find its outcome based on '_knn ' vote
    truth = r->get_outcome();

    if ( guess * truth < 0 )
         errors++;    
  }

  accuracy = (double) errors / (double) _test.get_num_rows();
  cout<<" Testing yielded "<<errors<<" errors out of "<<
    _test.get_num_rows()<<endl;
  cout<<" " <<100*accuracy<<"% inaccuracy"<<endl;
  cout<<" "<<100*(1.00-accuracy)<<"% accuracy"<<endl;
}



int driver::classify_row() 
{
  int outcomes=0; 
  int i; 
  int random; 

  for( i=0; i<_k; i++)
    outcomes += _important[i][_num_cols-1] ; // sum up the neighbours outcomes
   
  // last element of _important array is the outcome 
  if(outcomes > 0 )
    return 1; 

  if( outcomes < 0 )
    return -1; 

  // else then they must be equal....randomly pick between categories
  // note: this only will possibly  happen if _k is an even number
  random = rand() % 1; // make 0 or 1 
  if( random == 1 )
    return 1; 
  else 
    return -1;
}

void driver::find_important()// finds important vectors 
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
      random = rand() % _train.get_num_rows(); // pull random important vectors

      for( j=0; j<curr_size; j++)//loop through checking to see if its been used
	if(random != used_rows[j] )// if it is a new number
	  valid++;// if any bad number it will make it invalid

      for(once=once; once<1; once++)//first time the number is valid. 
	  valid++ ;
    }
    used_rows[curr_size] = random; // store which valid row we just found
    curr_size ++;   //add one to current used_row size; 
  
    temp_row = _train.get_row( random );// pull out the random tow from train 
    // store the elements in our important set
    for(k=0; k<_num_cols-1; k++)// object doesn't store outcome in array
      _important[i][k] = temp_row->get_col_data( k ); 
     
    // store outcome in last element ( _num_cols element)
    _important[i][k] =  temp_row->get_outcome();  
  }
}


// sorts the important vectors in closest to farthest order
void driver::sort_important( row * r )
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
       distance1 = get_dist( r->get_row_data(), _important[i] ); // get distance1
       distance2 = get_dist( r->get_row_data(), _important[i+1]); // get distance2
              
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



// finds the geometric distance between train vector and test vector
double driver::get_dist( double * train , double * test )
{
  int i;
  double temp=0;
  double distance=0; 

  for(i=0; i<_num_cols-1; i ++)
    temp += pow( (train[i] - test[i]), 2); /* square it */ 

  distance = sqrt(temp); 
  return distance; 
}


void driver::print( )
{
  int i, j;
  
  for( i=0; i<_IMPORTANT_SIZE; i++)
  {
    for( j=0; j<_num_cols; j++)
      cout<<_important[i][j]<<" ";
    
    cout<<endl; 
  }
}


void driver::check_valid_input()
{
  if( _k > _IMPORTANT_SIZE)
  {
    cerr<<" Invalid k dimension!! "<<endl;
    exit(1); 
  }

  if( _train.get_num_cols() != _test.get_num_cols())
  {
    cerr<<" train and test files are of incompatible dimensions!!" <<endl;
    exit(1); 
  }

  if( _IMPORTANT_SIZE > _train.get_num_rows() )
  {
    cerr<<" Invalid important vector dimensions!!"<<endl;
    exit(1);
  }
}
