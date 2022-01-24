#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Gmpq.h>

// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;


int floor_to_int(const CGAL::Quotient<CGAL::Gmpq> & x)
{
 int a = std::floor(CGAL::to_double(x));
 while (a > x) a -= 1;
 while (a+1 <= x) a += 1;
 return a;
}


int ceil_to_int(const CGAL::Quotient<CGAL::Gmpq> & x)
{
 double a = std::ceil(CGAL::to_double(x));
 while (a+1 >= x) a -= 1;
 while (a < x) a += 1;
 return a;
}

void testcase()
{
  
  // set the coefficients of A and b
  Program lp;
  int n, d;
  while(true) {
    cin >> n;
    if(n == 0) {
      return;
    }
    cin >> d;
    
    lp = Program(CGAL::SMALLER, false, 0, false, 0);
    for(int i = 0; i < n; i++) {
      vector<int> curr_constraints(d);
      long curr_len = 0;
      for(int j = 0; j < d; j++) {
        int a_ij; cin >> a_ij;
        curr_constraints[j] = a_ij;
        curr_len += a_ij * a_ij;
        lp.set_a(j, i,  IT(a_ij));
      }
      curr_len = sqrt(curr_len);
      
      int b_i; cin >> b_i;
      lp.set_b(i,  IT(b_i));
      lp.set_a(d, i,  IT(curr_len));
    }
    
    lp.set_l(d, true, 0); // radius nonnegative
    lp.set_c(d, -1); // maximize radius (i.e. minimize inverse)
    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_unbounded()) {
      cout << "inf" << endl;
    } else if(s.is_infeasible()) {
      cout << "none" << endl;
    } else {
      // cerr << s << endl;
      auto val = s.objective_value();
      // actually useless here to round since its an integer, anyway
      cout << floor_to_int(-val) << endl;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  testcase();
}

