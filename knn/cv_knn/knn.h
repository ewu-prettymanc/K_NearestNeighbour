#ifndef __KNN_H__
#define __KNN_H__

#define _IMPORTANT_SIZE 30

#include"data_set.h"
#include <math.h>

class knn
{  
 public:

  //constructor
  // ame: knn
  // desc: allocates a 2d array of doubles. 
  // params: int num_cols
  // returns: void
  knn( int num_cols );

  //desctructor
  // name: ~knn
  // desc: deletes each element of the _important vector array..then deletes the
  // important array. 
  // params: n/a
  ~knn();

  //   name: find_important
  // desc: randomly selects and stores important vectors from thetrain data set.
  //  Making sure it doesn't select the same row twice. 
  // params: data_set * traind
  // returns: void
  void find_important(data_set * train);// finds important vectors 

  // name: sort_important
  // desc:  sorts the rows in our _important array according to the geometric 
  // distance of the row given and the current  row of _important array. 
  // params: row * r
  // returns: void 
  void sort_important( row * r );

  //  name: classify_row
  // desc: classifies the row by the average of the first _k outcomes
  // params: int kVal
  // returns: int
  int classify_row(int kVal) ;

  // name: print
  // desc: prints the _important array
  // params: noe
  // returns: void
  void print( );

  
 protected:

  // Step 2 of sort_important
  // name: get_dist
  // params: double * train, double test 
  // desc: calculates thesum of the geometric distances between each given array
  // params: double * traind, double * test
  // returns: double
  double get_dist( double * train , double * test );

  int _num_cols;
  double ** _important; 
  double _outcome; 
  
};

#endif
