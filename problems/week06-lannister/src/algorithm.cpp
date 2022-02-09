///4
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


long floor_to_int(const CGAL::Quotient<CGAL::Gmpz> & x)
{
 double a = std::floor(CGAL::to_double(x));
 while (a > x) a -= 1;
 while (a+1 <= x) a += 1;
 return a;
}


long ceil_to_int(const CGAL::Quotient<CGAL::Gmpz> & x)
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
  int n, m;
  long s;
  cin >> n; cin >> m; cin >> s;
  // sewage canal ax+by+c = 0
  const int a = 0;
  const int b = 1;
  const int c = 2;
  // create an LP with Ax <= b, no lower bound and no upper bounds
  lp = Program(CGAL::SMALLER, false, 0, false, 0);
  vector<pair<long,long>> nobles(n);
  vector<pair<long,long>> commons(m);
  long sum_x_nobles = 0; long sum_y_nobles = 0;
  long sum_x_commons = 0; long sum_y_commons = 0;
  for(int i = 0; i < n; i++) {
    long x; std::cin >> x;
    long y; std::cin >> y;
    nobles[i].first = x; nobles[i].second = y;
    // set up constraint a x + b y + c <= 0
    lp.set_a(a, i, x);
    lp.set_a(b, i, y);
    lp.set_a(c, i, 1);
    sum_x_nobles += x;
    sum_y_nobles += y;
  }
  
  for(int i = 0; i < m; i++) {
    long x; std::cin >> x;
    long y; std::cin >> y;
    commons[i].first = x; commons[i].second = y;
    // set up constraint a x + b y + c >= 0
    lp.set_a(a, i + n, -x);
    lp.set_a(b, i + n, -y);
    lp.set_a(c, i + n, -1);
    sum_x_commons += x;
    sum_y_commons += y;
  }
  // enforce that a is one
  lp.set_l(a, true, 1);
  lp.set_u(a, true, 1);
  
  ///////////////////////////////////// left/right constraint
  Solution sol = CGAL::solve_linear_program(lp, ET());
  if(sol.is_infeasible()) {
    cout << "Yuck!" << endl;
    return;
  }
  ///////////////////////////////// sum of horizontal distances to sewage canal
  if(s != -1) {
    // cerr << sum_y_commons - sum_y_nobles << endl;
    lp.set_a(b, m + n, sum_y_commons - sum_y_nobles);
    lp.set_a(c, m + n, m - n);
    lp.set_b(m + n, s - sum_x_commons + sum_x_nobles);
    
    Solution sol = CGAL::solve_linear_program(lp, ET());
    if(sol.is_infeasible()) {
      cout << "Bankrupt!" << endl;
      return;
    }
  }
  
  int num_a = m + n + 1;
  ////////////////////////////////////// freshwater canal a2 x+b2 y+ c2 = 0
  const int a2 = 3;
  const int b2 = 4;
  const int c2 = 5;
  const int r = 6; // r is the max residual, i.e. longest freshwater pipe
  
  // enforce that b2 is one
  lp.set_l(b2, true, 1);
  lp.set_u(b2, true, 1);
  // residual nonnegative
  lp.set_l(r, true, 0);
  
  
  for(int i = 0; i < n; i++) {
    long x = nobles[i].first; long y = nobles[i].second;
    // set up constraint | a2 x + c2 + y | <= r 
    lp.set_a(a2, num_a + 2 * i, x);
    lp.set_a(c2, num_a + 2 * i, 1);
    lp.set_a(r, num_a + 2 * i, -1);
    lp.set_b(num_a + 2 * i, -y);
    
    lp.set_a(a2, num_a + 2 * i + 1, -x);
    lp.set_a(c2, num_a + 2 * i + 1, -1);
    lp.set_a(r, num_a + 2 * i + 1, -1);
    lp.set_b(num_a + 2 * i + 1, y);
  }
  
  num_a += 2 * n;
  for(int i = 0; i < m; i++) {
    long x = commons[i].first; long y = commons[i].second;
    // set up constraint | a2 x + c2 + y | <= r 
    lp.set_a(a2, num_a + 2 * i, x);
    lp.set_a(c2, num_a + 2 * i, 1);
    lp.set_a(r, num_a + 2 * i, -1);
    lp.set_b(num_a + 2 * i, -y);
    
    lp.set_a(a2, num_a + 2 * i + 1, -x);
    lp.set_a(c2, num_a + 2 * i + 1, -1);
    lp.set_a(r, num_a + 2 * i + 1, -1);
    lp.set_b(num_a + 2 * i + 1, y);
  }
  
  num_a += 2 * m;
  
  // have b1 == -a2
  lp.set_a(b, num_a + 1, 1);
  lp.set_a(a2, num_a + 1, 1); // b1 + a2 <= 0
  lp.set_a(b, num_a + 2, -1);
  lp.set_a(a2, num_a + 2, -1); // -b1 - a2 <= 0
  
  
  lp.set_c(r, 1); // minimize residual
  sol = CGAL::solve_linear_program(lp, ET());
  if(sol.is_infeasible()) {
    cout << "sth went wrong" << endl;
    return;
  } else {
    auto val = sol.objective_value();
    // cerr << s << endl;
    cout << ceil_to_int(val) << endl;
  }
  
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  while(t--) testcase();
}

