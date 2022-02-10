// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

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

struct warehouse {
  long x;
  long y;
  long s;
  long a;
};

struct stadium {
  long x;
  long y;
  long d;
  long u;
};

long floor_to_long(const CGAL::Quotient<CGAL::Gmpz>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase()
{
  int n, m, c;
  std::cin >> n >> m >> c;
  
  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp(CGAL::SMALLER, true, 0, false, 0);

  std::vector<warehouse> warehouses(n);
  std::vector<stadium> stadiums(m);

  std::vector<K::Point_2> points;
  points.reserve(n+m);
  for(int i = 0; i < n; i++) {
    long x, y, s, a;
    std::cin >> x >> y >> s >> a;
    warehouses[i] = {x, y, s, a};
    points.push_back(K::Point_2(x,y));
    for(int j = 0; j < m; j++) {
      // set upper constraints for supply, can't sell more in total
      // sum_{j} delivery(w_i->stad_j) <= s_i
      lp.set_a(i * m + j, i, 1);
      lp.set_b(i, s);
    }
  }
  
  for(int j = 0; j < m; j++) {
    int x, y; long d, u;
    std::cin >> x >> y >> d >> u;
    stadiums[j] = {x, y, d, u};
    points.push_back(K::Point_2(x,y));
    for(int i = 0; i < n; i++) {
      // set upper constraints for alcohol, can't get more in total
      // sum_{i} alcohol(w_i->stad_j) <= 100 * u_j
      // (factor 100 because pure alcohol is in percent)
      long ai = warehouses[i].a;
      lp.set_a(i * m + j, n + j, ai);
      lp.set_b(n + j, 100 * u);

      // supply == demand
      lp.set_a(i * m + j, n + m + j, 1);
      lp.set_b(n + m + j, d);
      lp.set_a(i * m + j, n + 2 * m + j, -1);
      lp.set_b(n + 2 * m + j, -d);
    }
  }
  
  std::vector<std::vector<int>> revs(n, std::vector<int>(m, 0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      int rws;
      std::cin >> rws;
      revs[i][j] = rws;
      // for testsets 1/2
      // lp.set_c(i * m + j, -rws);
    }
  }

  
  Triangulation t;
  t.insert(points.begin(), points.end());

  std::vector<std::pair<K::Point_2, long>> contours;
  contours.reserve(100); // assumptions for last test case has this true

  for(int i = 0; i < c; i++) {
    int x, y; long r;
    std::cin >> x >> y >> r;
    auto p = K::Point_2(x,y);
    auto dist = CGAL::squared_distance(p, t.nearest_vertex(p)->point());
    if(dist < r * r) {
      contours.push_back({p, r * r});
    }
  }
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      auto p_w = K::Point_2(warehouses[i].x, warehouses[i].y);
      auto p_s = K::Point_2(stadiums[j].x, stadiums[j].y);
      int num_contours = 0;
      for(auto cp : contours) {
        double dist_w = CGAL::squared_distance(p_w, cp.first);
        double dist_s = CGAL::squared_distance(p_s, cp.first);
        bool inside_w = (dist_w < cp.second);
        bool inside_s = (dist_s < cp.second);
        if((!inside_s && inside_w) || (inside_s && !inside_w))
          num_contours++;
      }
      lp.set_c(i * m + j, -100 * revs[i][j] + num_contours);
    }
  }

  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()) {
    std::cout << "RIOT!" << std::endl;
    return;
  } else {
    auto val = s.objective_value();
    std::cout << floor_to_long(-val / 100) << std::endl;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  std::size_t t;
  for (std::cin >> t; t > 0; --t)
    testcase();
  return 0;
}