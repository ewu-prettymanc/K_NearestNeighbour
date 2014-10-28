#include "perceptron.h"

perceptron::perceptron(int howmany, double learn)
  : _num_weights(howmany), _learn_rate(learn)
{
  int i;

  _weights = new double[_num_weights];
  assert(_weights);
  
  for ( i = 0; i < _num_weights; i ++ )
  {
    _weights[i] = (double) rand() / (double) RAND_MAX;
    _weights[i] *= 2;
    _weights[i] -= 1;
  }

  _threshold = (double) rand() / (double) RAND_MAX;
  _threshold *= 2;
  _threshold -= 1;
  
}

perceptron::~perceptron()
{
  delete [] _weights;
}

double perceptron::classify_row(row * r)
{
  int i;
  double total = 0;

  for ( i = 0; i < _num_weights; i ++ )
    total += _weights[i] * r->get_col_data(i);

  if ( total > _threshold )
    return 1;
  
  return -1;
}

void perceptron::update(row * r)
{
  int i;
  double error = r->get_outcome() - classify_row(r);

  for ( i = 0; i < _num_weights; i ++ )
    _weights[i] += error * _learn_rate * r->get_col_data(i);

  _threshold -= error * _learn_rate;
}

void perceptron::print()
{
  int i;
  cout<<"weights:"<<endl;
  for ( i = 0; i < _num_weights; i ++ )
    cout<<_weights[i]<<endl;

  cout<<"threshold: "<<_threshold<<endl;
}
