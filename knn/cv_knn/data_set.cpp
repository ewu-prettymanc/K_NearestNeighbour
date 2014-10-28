
#include"data_set.h"


data_set::data_set(char * filename)
{
  int i;
  ifstream in;

  in.open(filename);

  if ( ! in.is_open()  )
  {
    cerr<<"could not open "<<filename<<endl;
    exit(1);
  }

  in>>_num_rows;
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

  for ( i = 0; i < _num_rows; i ++ )
    delete _data[i];

  delete [] _data;
}

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
