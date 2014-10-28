#ifndef __DATA_SET_H__
#define __DATA_SET_H__

#include"row.h"
#include <math.h> 

#define REDUCTION_CONSTANT  .5

class data_set
{
 public:

  data_set(char * filename);
  ~data_set();

  row* get_row(int which);


  int get_num_cols();
  int get_num_rows();
  row ** get_data();
  char * _filename; 

  void sort_data( data_set * train, int for_which );
  void cluster_data( );
  int classify_row(int kVal, data_set * trained ) ;
  int get_truth( int which );
  void print_data();
  int get_curr_size();
  
    
 protected:

  double get_dist( double * test , double * train );
  double* average_rows( double * data1, double * data2 );

  int _num_rows;
  int _curr_size; 
  int _reduction_size; 
  int _num_cols;
  row ** _data;

};


/*
 data set
  members:
   -an array of row objects
   -how many rows
   -how many cols
  methods:
   -return a pointer to a row
   -read from a file ( CONSTRUCTOR )
   
*/

#endif
