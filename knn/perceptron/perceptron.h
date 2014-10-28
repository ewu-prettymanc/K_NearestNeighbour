
#include"data_set.h"

class perceptron
{
 public:

  perceptron(int howmany, double learn=.1);
  ~perceptron();

  double classify_row(row * r);
  void update(row * r);
  void print();
  

 protected:

  double * _weights;
  int _num_weights;
  double _threshold;
  double _learn_rate;

};


/*
 perceptron
  members: 
  -an array of weights ( cols - 1 ) 
  -howmany weights
  -threshold
  -learn rate ( larger values mean bigger changes )
  methods:
  -classify a row
  -update ( in case it is wrong )
  -init ( CONSTRUCTOR )
  -print the weights and threshold
*/
