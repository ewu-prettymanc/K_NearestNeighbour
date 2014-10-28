#include"driver.h"
#include<time.h>

/*
Main:
name: main
desc: is given command line arguements. Seed's the random generater. Allocates
a new 
driver object. Calculates the outcome .
params: argc, char ** argv
returns: int
1) make sure we have the correct number of command line arguements. 
2) seed the random with a time of 0
3) allocate a new driver. with argv[1], argv[2], and atoi[3] as parameters. 
   // note we need to convert paramter 3 from a character an intiger
4) calculate the outcome of the test file. 
*/ 
int main(int argc, char ** argv )
{
  if ( argc != 4 )
  {
    cerr<<"Usage: "<<argv[0]<<" <training file> <testing file> <k-value>"<<endl;
    return 1;
  }

  srand(time(0));

  driver data( argv[1], argv[2], atoi(argv[3]) );

  data.calc_outcome();

  return 0;
}
