/*
* from https://arma.sourceforge.net/docs.html#example_prog
*
* pasted by: Peratham Wiriyathammabhum
*/

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
  {
  mat A(4, 5, fill::randu);
  mat B(4, 5, fill::randu);
  
  cout << A*B.t() << endl;
  
  return 0;
  }
