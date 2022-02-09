///
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
  Program lp;
  int n, m;
  while(true) {
    cin >> n; cin >> m;
    if(n == 0 && m == 0) {
      return;
    } else {
      // create an LP with Ax <= b, lower bound 0 and no upper bounds
      lp = Program(CGAL::SMALLER, true, 0, false, 0);
      vector<int> prices(m);
      vector<pair<int,int>> nutrients(n);
      for(int i = 0; i < n; i++) {
        cin >> nutrients[i].first; cin >> nutrients[i].second;
        lp.set_b(i, nutrients[i].second);
        lp.set_b(i + n, -nutrients[i].first);
      }
      for(int j = 0; j < m; j++) {
        cin >> prices[j];
        for(int i = 0; i < n; i++) {
          int C_ji; cin >> C_ji;
          lp.set_a(j, i,  C_ji);  // x^T * C[:,i]  <= max_i
          lp.set_a(j, i + n,  -C_ji);  // -x^T * C[:,i]  <= min_i
        }
        // objective function
        lp.set_c(j, prices[j]);    
      }
      // solve the program, using ET as the exact type
      Solution s = CGAL::solve_linear_program(lp, ET());
      if(s.is_unbounded()) {
        cout << "unbounded" << endl;
      } else if(s.is_infeasible()) {
        cout << "No such diet." << endl;
      } else {
        auto val = s.objective_value();
        // cerr << s << endl;
        cout << floor_to_int(val) << endl;
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  testcases();
}

