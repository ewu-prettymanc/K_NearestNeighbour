#ifndef __ROW_H__
#define __ROW_H__

#include<iostream>
#include<fstream>
#include<assert.h>
#include<stdlib.h>

using namespace std;

class row
{
 public: // anybody can access

  row(ifstream * file, int num_cols);
  ~row();  //~objectname is a destructor
           // NO PARAMETERS EVER!  ONE DESTRUCTOR PER CLASS

  double get_col_data(int which_one);
  double get_outcome();
  double * get_row_data(); 
  

 protected: // only methods in this object or children objects can access

  int _num_cols;
  double * _data; 
  double _outcome;

};


/*
 row object
  members:
   -howmany cols
   -the data ( cols -1 in size )
   -outcome 
  methods:
   -read itself a file ( CONSTRUCTOR )
   -return a col
   -return the outcome
 */
#endif
