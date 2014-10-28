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

  _knn = new knn(_train.get_num_cols() ); 
  assert( _knn); 
  
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
  delete _knn; 
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
  int i, once=0, k;
  double truth, guess, accuracy;
  row * r;
  int errors;
  int lowest_error;  

  for( k=0; k< ITERATIONS ;k ++ )
    // try a new set of important vectors...if it is better then use that set. 
  {
    errors = 0; 
    _knn->find_important( & _train); // generate a new set of important vectors

    for ( i = 0; i < _test.get_num_rows(); i ++ )
    {
      r = _test.get_row(i);// pull out a row to be tested      
      _knn->sort_important( r ); 
      // sorts important vectors accoring to this test vector
      
      guess = _knn->classify_row( _k );// find its outcome based on '_knn ' vote
      truth = r->get_outcome();
      
      if ( guess * truth < 0 )
	errors++;    
    }

    for(once=once; once<1; once++)// the first time will be our new lowest
    {
      lowest_error = errors; 
      cout<<"Calculating"; 
    }
    cout.flush(); //flush the buffer to the command prompt

    cout<<".";
    // I was hoping to print a slider of dots...but apparently it 
    // only prints while in a while loop if the cout contains a new line 
    // character :( :(..
    
    if( errors < lowest_error)// if errors is lower its a new low
     lowest_error = errors; 
  }

  cout<<endl;
  accuracy = (double) lowest_error / (double) _test.get_num_rows();
  cout<<" After testing "<<ITERATIONS<<" different sets of important vectors, "
      <<endl;
  cout<<" The Best Testing yielded "<<lowest_error<<" errors out of "<<
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
  if( _k > _IMPORTANT_SIZE || _k < 1 )// why have a k of 0 ??..no duh
  {
    cerr<<" Invalid k dimension!! "<<endl;
    exit(1); 
  }

  if( _train.get_num_cols() != _test.get_num_cols())
  {
    cerr<<" Invalid train and test file dimensions!! " <<endl;
    exit(1); 
  }

  if( _IMPORTANT_SIZE > _train.get_num_rows() )
  {
    cerr<<" Invalid important vector dimensions!! "<<endl;
    exit(1);
  }
}
