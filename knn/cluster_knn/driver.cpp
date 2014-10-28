#include "driver.h"


//constructor
/*
name: driver
desc: Checks to make sure all user input is valid then allocates a new knn 
object.
params: char * train, char * test, int kVal
returns: n/a
1) check to make sure it is valid input		(F)
2) allocate a new knn object	  		
*/
// access 2d array by array[row][col]
driver::driver(char * train, char * test, int kVal)
  : _train(train), _test(test), _k(kVal)
{  
  check_valid_input(); 
}

//destructor
/*
name: ~driver
desc: delets the _knn member
params: n/a
returns: n/a
1) delete _knn
*/
driver::~driver()
{ 
}

/*
name: calc_outcome
desc: trains a set of important vectors for each tested vector and then 
calculates an outcome by taking a majority vote from k of its closest neighbours
It selects a new set of important vectors a certain ITERATION number of times. 
It prints out the results of the most accurate testing
params:none
returns: void
1) for ITERATION number of times do steps 2 - 8 		(L)
2) find an important set of vectors
3) for each row of the test file do steps 4-6			(L)
4) sort the important vectors according to that row				
5) classify the outcome of that row
6) keep a running tab of how many errors we produce
7) for the first time in the loop the lowest error score gets the errors
8) every other time if the new errors is lower then the lowest so far
 give it that erros value  
9) print the accuracy of the testing 
*/
void driver::calc_outcome()
{
  int i;
  int once=0, errors=0;
  int truth, guess;
  double accuracy; 
 

  for( i=0; i<_test.get_num_rows(); i++)
    {
        _test.sort_data( & _train, i );
    
      // clustering should only need to accure once...they will naturally
      // be set close to similare vectors due to the previouse sort
      for( ; once < 1; once ++)
	_train.cluster_data( );
     

      guess =  _test.classify_row( _k, & _train ); 
      truth = _test.get_truth( i ); 

      if( guess * truth < 0 )
	errors ++ ;  
    }

  accuracy = (double) errors / (double) _test.get_num_rows();
  cout<<" After clustering the training set "<<endl;
  cout<<" Testing yielded "<<errors<<" errors out of "<<
    _test.get_num_rows()<<endl;
  cout<<" " <<100*accuracy<<"% inaccuracy"<<endl;
  cout<<" "<<100*(1.00-accuracy)<<"% accuracy"<<endl;
}

//Step 1 of driver
/* 
name: check_valid_input
desc: checks valid k dimension. valid traind and test files. and valid 
important vector size. 
params: none
returns: void
1) check k isn't greater then IMPORTANT_SIZE
2) check valid train and test file dimensions
3) check valid IMPORTANT_SIZE compared to train size 
*/
void driver::check_valid_input()
{
  if( _k > REDUCTION_CONSTANT*_train.get_num_rows()  )
  {
    cerr<<" Invalid k dimension!! "<<endl;
    exit(1); 
  }

  if( _train.get_num_cols() != _test.get_num_cols())
  {
    cerr<<" train and test files are of incompatible dimensions!!" <<endl;
    exit(1); 
  }

  if( REDUCTION_CONSTANT * _train.get_num_rows() > _train.get_num_rows() )
  {
    cerr<<" Invalid  REDUCTION_CONSTANT!!"<<endl;
    exit(1);
  }
}
