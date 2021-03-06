#include"row.h"

row::row(ifstream * file, int num_cols)
  : _num_cols(num_cols)  // an initialization list 
{
  int i;

  _data = new double[_num_cols-1];
  assert(_data);

  (*file)>>_outcome;

  for ( i = 0; i < _num_cols - 1; i ++ )
    (*file)>>_data[i];
  
}

row::~row()
{
  delete [] _data;
}

double row::get_col_data(int which_one)
{
  assert(which_one >= 0 && which_one < _num_cols);

  return _data[which_one];
}

double row::get_outcome()
{
  return _outcome;
}

double * row::get_row_data( )
{
  return _data; 
}

void row::update_row( double * new_row )
{
  int i; 
  for( i=0; i<_num_cols-1; i++)
    _data[i] = new_row[i]; 
  
}

void row::print_row()
{
  int i; 
  
  for( i=0; i<_num_cols-1; i++)
    cout<<_data[i]; 
}
