#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "knn.h"
#define ITERATIONS 50

class driver
{
 public:

  //constructor
  // name: driver
  // desc: Checks to make sure all user input is valid then allocates a new knn 
  // object.
  // params: char * train, char * test, int kVal
  // returns: n/a
  driver(char * train, char * test, int kVal);

  //destructor
  // name: ~driver
  // desc: delets the _knn member
  // params: n/a
  // returns: n/a
  ~driver();

  // name: calc_outcome
  // desc: trains a set of important vectors for each tested vector and then 
  // calculates an outcome by taking a majority vote from k of its closest 
  //neighbours
  // It selects a new set of important vectors a certain ITERATION number of
  // times. 
  // It prints out the results of the most accurate testing
  // params:none
  // returns: void
  void calc_outcome();
  
 
 private:
  
  //Step 1 of driver 
  // name: check_valid_input
  // desc: checks valid k dimension. valid traind and test files. and valid 
  // important vector size. 
  // params: none
  // returns: void
  void check_valid_input();

  data_set _train;
  data_set _test;
  knn * _knn;
  int _k; 
};

#endif
