// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Gmpq.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;


int floor_to_int(const CGAL::Quotient<CGAL::Gmpz> & x)
{
 int a = std::floor(CGAL::to_double(x));
 while (a > x) a -= 1;
 while (a+1 <= x) a += 1;
 return a;
}


int ceil_to_int(const CGAL::Quotient<CGAL::Gmpz> & x)
{
 double a = std::ceil(CGAL::to_double(x));
 while (a+1 >= x) a -= 1;
 while (a < x) a += 1;
 return a;
}

void testcases()
{
  
  // set the coefficients of A and b
  const int X = 0; 
  const int Y = 1;
  const int Z = 2;
  Program lp;
  int p, a, b;
  while(true) {
    cin >> p;
    if(p == 0) {
      return;
    } else if(p == 1) { // prob 1
      cin >> a; cin >> b;
      // create an LP with Ax <= b, lower bound 0 and no upper bounds
      lp = Program(CGAL::SMALLER, true, 0, false, 0); 
      lp.set_a(X, 0,  1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);    // x + y  <= 4
      lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a * b); // 4x + 2y <= ab
      lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);    // -x + y <= 1
      // objective function, minimize by flipping signs
      lp.set_c(X, a);                                           // ax
      lp.set_c(Y, -b);                                          // -by
    } else {
      cin >> a; cin >> b;
      
      // create an LP with Ax <= b, lower bound 0 and no upper bounds
      lp = Program(CGAL::SMALLER, false, 0, true, 0); 
      lp.set_a(X, 0,  -1); lp.set_a(Y, 0, -1);// lp.set_a(Z, 0, 0); 
      lp.set_b(0, 4);    // -x - y  <= 4
      lp.set_a(X, 1, -4);  lp.set_a(Y, 1, -2); lp.set_a(Z, 1, -1); lp.set_b(1, a * b); // 4x + 2y <= ab
      lp.set_a(X, 2, 1);   lp.set_a(Y, 2, -1); //lp.set_a(Z, 2, 0);  
      lp.set_b(2, 1);    // x - y <= 1
      // objective function, minimize by flipping signs
      lp.set_c(X, a);                                          // ax
      lp.set_c(Y, b);                                          // by
      lp.set_c(Z, 1);                                          // z
      
    }
    
    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_unbounded()) {
      cout << "unbounded" << endl;
    } else if(s.is_infeasible()) {
      cout << "no" << endl;
    } else {
      auto val = s.objective_value();
      if(p == 1) { // max problem
        cerr << s << endl;
        cout << -ceil_to_int(val) << endl;
      } else { // min problem
        cout << ceil_to_int(val) << endl;
      }
    }
  }
}


int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  testcases();
}

