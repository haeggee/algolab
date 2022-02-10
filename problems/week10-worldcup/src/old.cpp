///3
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>


// for triangulation
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;


long floor_to_long(const CGAL::Quotient<CGAL::Gmpq> & x)
{
 double a = std::floor(CGAL::to_double(x));
 while (a > x) a -= 1;
 while (a+1 <= x) a += 1;
 return a;
}

void testcase()
{
  
  // set the coefficients of A and b
  Program lp;
  int n, m, c;
  cin >> n; cin >> m; cin >> c;
  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  lp = Program(CGAL::SMALLER, true, 0, false, 0);
  
  vector<K::Point_2> pts;
  pts.reserve(n + m);
  
  vector<tuple<long,long,long,long>> warehouse(n);
  vector<tuple<long,long,long,long>> stadium(m);
  
  for(int i = 0; i < n; i++) {
    long x, y, s, a;
    std::cin >> x >> y >> s >> a;
    warehouse[i] = {x,y,s,a};
    
    pts.push_back(K::Point_2(x,y));
    // set up constraint \sum_s x_w,s <= s_w
    for(int j = 0; j < m; j++) {
      lp.set_a(i * m + j, i, 1);
      lp.set_b(i, s);
    }
  }
  
  for(int j = 0; j < m; j++) {
    long x, y, d, u;
    std::cin >> x >> y >> d >> u;
    stadium[j] = {x,y,d,u};
    
    pts.push_back(K::Point_2(x,y));
    for(int i = 0; i < n; i++) {
      int a_w = std::get<3>(warehouse[i]);
      // upper bound alcohol
      lp.set_a(i * m + j, n + 3 * j, a_w);
      lp.set_b(n + 3 * j, 100 * u);
      // supply == demand
      lp.set_a(i * m + j, n + 3 * j + 1, -1);
      lp.set_b(n + 3 * j + 1, -d);
      lp.set_a(i * m + j, n + 3 * j + 2, 1);
      lp.set_b(n + 3 * j + 2, d);
    }
  }
  
  vector<int> r(n * m);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      int r_ws; std::cin >> r_ws;
      r[i * m + j] = r_ws;
    }
  }
  
  //////////////////////////////////// 
  
  
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  vector<tuple<long,long,long>> contours;
  contours.reserve(100); // according to assumptions that's enough
  for(int i = 0; i < c; i++) {
    long x, y, r;
    std::cin >> x >> y >> r;
    K::Point_2 p = K::Point_2(x,y);
    auto v = t.nearest_vertex(p);
    auto dist = CGAL::squared_distance(v->point(), p);
    
    if(dist < r * r) {
      contours.push_back({x,y,r * r});
    }
  }
  
  for(int i = 0; i < n; i++) {
    K::Point_2 wareho = K::Point_2(get<0>(warehouse[i]), get<1>(warehouse[i]));
    for(int j = 0; j < m; j++) {
      K::Point_2 stad = K::Point_2(get<0>(stadium[j]), get<1>(stadium[j]));
      int t_ws = 0;
      for(auto cont : contours) {
        K::Point_2 cp = K::Point_2(get<0>(cont), get<1>(cont));
        auto d1 = CGAL::squared_distance(wareho, cp) < get<2>(cont);
        auto d2 = CGAL::squared_distance(stad, cp) < get<2>(cont);
        if((d1 && !d2) || (!d1 && d2)) { // only traverse if only one is inside; we know they do cross only once
          t_ws++;
        }
      }
      lp.set_c(i * m + j, -100 * r[i * m + j] + t_ws);
    }
  }
  
  
  //////////////////////////////////// solve
  Solution sol = CGAL::solve_linear_program(lp, ET());
  // cerr << sol << endl;
  
  if(sol.is_infeasible()) {
    cout << "RIOT!" << endl;
    return;
  } else {
    auto val = sol.objective_value();
    cout << floor_to_long(-val / 100) << endl;
  }
  
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  while(t--) testcase();
}
