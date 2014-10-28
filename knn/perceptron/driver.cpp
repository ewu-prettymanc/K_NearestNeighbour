#include "driver.h"


driver::driver(char * train, char * test)
  : _train(train), _test(test)
{

  _thinker = new perceptron(_train.get_num_cols() - 1);
  assert( _thinker );
}

driver::~driver()
{
  delete _thinker;
}

void driver::perform_training()
{
  int num_errors;
  int i;
  num_errors = make_one_pass();
  
  for ( i = 0; i < 10000 && num_errors > 0; i ++ )
    num_errors = make_one_pass();


  cout<<"After "<<i<<" passes, the error is "<<num_errors<<endl;
}

int driver::make_one_pass()
{
  int i, errors = 0;
  double truth, guess;
  row * r;

  for ( i = 0; i < _train.get_num_rows(); i ++ )
  {
    r = _train.get_row(i);
    guess = _thinker->classify_row( r );
    truth = r->get_outcome();
    /*
    cout<<"Percoptron is: "<<endl;
    _thinker->print();
    cout<<"guess is "<<guess<<endl;
    cout<<"truth is "<<truth<<endl;
    int b;
    cin>>b;
    */
    if ( guess * truth < 0 )
    {
      _thinker->update(r);
      errors++;
    }
    
  }

  return errors;
}


void driver::perform_testing()
{
  int i, errors = 0;
  double truth, guess;
  row * r;
  
  for ( i = 0; i < _test.get_num_rows(); i ++ )
  {
    r = _test.get_row(i);
    guess = _thinker->classify_row( r );
    truth = r->get_outcome();

    if ( guess * truth < 0 )
    {
      _thinker->update(r);
      errors++;
    }
    
  }

  cout<<"Testing yielded "<<errors<<" errors."<<endl;
  cout<<"Percent Inaccurate is: "
      <<(double) errors / (double) _test.get_num_rows()<<endl;

  _thinker->print();
}
