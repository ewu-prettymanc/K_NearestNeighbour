#define _IMPORTANT_SIZE  30
#include "data_set.h"
#include <stdlib.h> 
#include <math.h> 
#include <time.h> 

class driver
{
 public:

  driver(char * train, char * test, int kVal);
  ~driver();

  void find_important();
  void calc_outcome();
  int classify_row(); 
 
 
 private:
  
  void sort_important( row * r );
  double get_dist( double * train , double * test );
  void print();
  void check_valid_input();

  double ** _important; 
  data_set _train;
  data_set _test;
  int _max_distance; 
  int _min_distance; 
  int _k; 
  int _num_cols; 
};
