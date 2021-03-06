
// BLAS level 3
// symmetric matrix (without adaptor) 

//#define BOOST_NO_FUNCTION_TEMPLATE_ORDERING

#include <stddef.h>
#include <iostream>
#include <boost/numeric/bindings/blas.hpp>
#include <boost/numeric/bindings/ublas/matrix.hpp>
#include <boost/numeric/bindings/upper.hpp>
#include <boost/numeric/bindings/lower.hpp>
#include "utils.h"

namespace ublas = boost::numeric::ublas;
namespace blas = boost::numeric::bindings::blas;
namespace bindings = boost::numeric::bindings;
namespace tag = boost::numeric::bindings::tag;

using std::cout;
using std::cin;
using std::endl; 

typedef double real_t; 

typedef ublas::matrix<real_t, ublas::column_major> cm_t; 
typedef ublas::matrix<real_t, ublas::row_major> rm_t; 

int main (int argc, char **argv) {
  size_t n = 0;
  if (argc > 1) {
    n = atoi(argv [1]);
  }

  cout << endl; 

  if (n <= 0) {
    cout << "n -> ";
    cin >> n;
  }
  cout << endl; 

  cm_t uc (n, n);
  cm_t lc (n, n); 
  rm_t ur (n, n); 
  rm_t lr (n, n); 

  init_symm (uc, 'u'); 
  init_symm (lc, 'l'); 
  init_symm (ur, 'u'); 
  init_symm (lr, 'l'); 

  print_m (uc, "a == uc");
  cout << endl; 
  print_m_data (uc, "uc");
  cout << endl; 

  print_m (lc, "a == lc");
  cout << endl; 
  print_m_data (lc, "lc");
  cout << endl; 

  print_m (ur, "a == ur");
  cout << endl; 
  print_m_data (ur, "ur");
  cout << endl; 

  print_m (lr, "a == lr");
  cout << endl; 
  print_m_data (lr, "lr");
  cout << endl; 

  cm_t cbl (n, n+1); 
  rm_t rbl (n, n+1); 
  cm_t ccl (n, n+1); 
  rm_t rcl (n, n+1); 

  init_m (cbl, rws1());
  init_m (rbl, rws1());

  print_m (cbl, "b == cb");
  cout << endl; 
  print_m (rbl, "b == rb");
  cout << endl; 

  blas::symm (tag::left(),  1., bindings::upper(uc), cbl, 0., ccl); 
  print_m (ccl, "c = a b");
  cout << endl; 

  blas::symm (tag::left(),  1., bindings::lower(lc), cbl, 0., ccl);  
  print_m (ccl, "c = a b");
  cout << endl; 

  blas::symm (tag::left(),  1., bindings::upper(ur), rbl, 0., rcl); 
  print_m (rcl, "c = a b");
  cout << endl; 

  blas::symm (tag::left(),  1., bindings::lower(lr), rbl, 0., rcl); 
  print_m (rcl, "c = a b");
  cout << endl; 
  
  cm_t cbr (n+1, n); 
  rm_t rbr (n+1, n); 
  cm_t ccr (n+1, n); 
  rm_t rcr (n+1, n); 

  init_m (cbr, cls1());
  init_m (rbr, cls1());
  
  print_m (cbr, "b == cb");
  cout << endl; 
  print_m (rbr, "b == rb");
  cout << endl; 

  blas::symm (tag::right(),  1., bindings::upper(uc), cbr, 0., ccr); 
  print_m (ccr, "c = b a");
  cout << endl; 

  blas::symm (tag::right(),  1., bindings::lower(lc), cbr, 0., ccr);  
  print_m (ccr, "c = b a");
  cout << endl; 

  blas::symm (tag::right(),  1., bindings::upper(ur), rbr, 0., rcr); 
  print_m (rcr, "c = b a");
  cout << endl; 

  blas::symm (tag::right(),  1., bindings::lower(lr), rbr, 0., rcr); 
  print_m (rcr, "c = b a");
  cout << endl; 

  cout << endl; 

}
