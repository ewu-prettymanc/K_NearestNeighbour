
#include"data_set.h"


data_set::data_set(char * filename)
{
  int i;
  ifstream in;

  in.open(filename);
  _filename = filename; 
  if ( ! in.is_open()  )
  {
    cerr<<"could not open "<<filename<<endl;
    exit(1);
  }

  in>>_num_rows;
  _curr_size = _num_rows;;
  in>>_num_cols;

  _data = new row*[_num_rows];
  assert(_data);

  for ( i = 0; i < _num_rows; i ++ )
  {
    _data[i] = new row( &in, _num_cols );
    assert( _data[i] );
  }

  in.close();

}


data_set::~data_set()
{
  int i;
  // cout <<"deleting this file "<<endl;

  // cout<<_filename<<endl; 
  

  for ( i = 0; i < _curr_size; i ++ )
      delete _data[i];
    
      

   delete [] _data;
}

// reduces the data down to a specified size
void data_set::cluster_data()
{
  int i, j; 
  _reduction_size = (int ) (_num_rows * REDUCTION_CONSTANT); 

  row ** training_data;
  double * temp_data; 

  sort_data( this , -1 ); 
  // we can sort with respect to any testing row 
  
  training_data = this->get_data(); 

   while( _curr_size > _reduction_size )
    for( i=0; i<_curr_size-1 && _curr_size >_reduction_size; i++)
      if( training_data[i]->get_outcome() == training_data[i+1]->get_outcome() )
	{
	  temp_data = average_rows(training_data[i]->get_row_data(), 
				   training_data[i+1]->get_row_data() ); 
	  
	  training_data[i]->update_row(  temp_data );
	  delete [] temp_data; 

	  // we've only changed the data...so the outcomes should still be the
	  // same therefor we don't need to change them 

	  delete training_data[i+1];
	  for( j=i+1; j<_curr_size-1; j++)
	    training_data[j]= training_data[j+1];// shift all the data back one
	 
	  _curr_size --; 
	} 
}

// averages the two rows with eachother 
double* data_set::average_rows( double * data1, double * data2 )
{
  int i; 
  double *  result = new double[_num_cols-1]; 
  assert(result); 
  
  for( i=0; i<_num_cols-1; i++)
      result[i] = (data1[i] + data2[i]) / 2;// average the two elements
  
  return result; 
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
void data_set::sort_data( data_set * train, int for_which )
// for_which is which row to sort according to
{
  int i, number_switched=1; // get into loop first time 
  double distance1, distance2; 
  row * temp_row; 
  row ** training_data; 
  int curr_size; 
  
  double  * zero_data = new double[_num_cols-1];
  assert( zero_data ); 
  for(i=0; i<_num_cols-1; i++)
    zero_data[i] = 1000000; // the origen we will sort with respect to 
 
  curr_size = train->get_curr_size(); 
  training_data = train->get_data(); // get a pointer to the training sets dataj
  
  
  // implement MERGE SORT... as many as needed times 
  //if we loop through the whole thing without having to switch any it is sorted
   while( number_switched != 0 )
   {
     number_switched = 0; // initialize howmany switched first 
     for( i=0; i<( curr_size-1); i++)
     {
       if( for_which < 0 )
	 {
	   distance1 = get_dist(  zero_data ,
				 training_data[i]->get_row_data() ); 

	   distance2 = get_dist(  zero_data , 
				 training_data[i+1]->get_row_data() ); 
	 }
       
       else
	 {
	   distance1 = get_dist( _data[for_which]->get_row_data(), 
				 training_data[i]->get_row_data() ); 
	   distance2 = get_dist( _data[for_which]->get_row_data(), 
				 training_data[i+1]->get_row_data() ); 
	 }


              
       // if distance2 is greater then distance1 then switch the rows 
       if( distance2 < distance1 )
       {
	 temp_row = training_data[i]; 
	 training_data[i] = training_data[i+1];
	 training_data[i+1] = temp_row; 
	 
	 number_switched ++ ; 
       }
     }
     // end of while loop 
   }
   delete [] zero_data; 
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
double data_set::get_dist( double * test , double * train )
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
int data_set::classify_row(int kVal, data_set * trained ) 
{
  int outcomes=0; 
  int i; 
  int random; 
  row ** trained_data; 

  trained_data = trained->get_data(); 

  for( i=0; i<kVal; i++)
    outcomes += trained_data[i]->get_outcome() ; 
  // sum up the neighbours outcomes
   
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

// prints the data; 
void data_set::print_data()
{
  int i; 
  
  for( i=0; i<_curr_size; i++)
    {
      _data[i]->print_row();

      cout<<endl;
    }
  
}

// miscellanous access methods-----------
row* data_set::get_row(int which)
{
  assert( which >= 0 && which < _num_rows );
  
  return _data[which];
}


int data_set::get_num_cols()
{
  return _num_cols;
}

int data_set::get_num_rows()
{
  return _num_rows;
}

row ** data_set::get_data()
{
  return _data;
}


int data_set::get_truth( int which )
{
  return _data[which]->get_outcome(); 
}


int data_set::get_curr_size()
{
  return _curr_size; 
}
