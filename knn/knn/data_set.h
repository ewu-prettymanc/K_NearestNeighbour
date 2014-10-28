
#include"row.h"

class data_set
{
 public:

  data_set(char * filename);
  ~data_set();

  row* get_row(int which);


  int get_num_cols();
  int get_num_rows();

 protected:

  int _num_rows;
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
