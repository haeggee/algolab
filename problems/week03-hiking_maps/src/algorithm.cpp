///1
#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Line_2 L;
// typedef std::tuple<int, int, int, int> leg;

using namespace std;


void testcase() {
  int m, n;
  cin >> m; cin >> n;
  vector<P> leg_points(m);
  for(int i = 0; i < m; i++) {
     int x, y; cin >> x; cin >> y;
     leg_points[i] = P(x, y);
  }
  
  vector<vector<int>> triang_covers_leg(n, vector<int>(0));

  for(int i = 0; i < n; i++) {
    vector<P> q(6);
    for(int j = 0; j < 6; j++) {
      int x, y; cin >> x; cin >> y;
      q[j] = P(x,y);
    }
    L e0 = L(q[0], q[1]);
    L e1 = L(q[2], q[3]);
    L e2 = L(q[4], q[5]);
    
    auto o0 = CGAL::intersection(e0,e1);
    const P* p0 = boost::get<P>(&*o0); // point intersec guaranteed
    auto o1 = CGAL::intersection(e0,e2);
    const P* p1 = boost::get<P>(&*o1); // point intersec guaranteed
    auto o2 = CGAL::intersection(e1,e2);
    const P* p2 = boost::get<P>(&*o2); // point intersec guaranteed
    vector<bool> covers_leg(m, false);
    for(int j = 0; j < m; j++) { // check for every point if it's covered
      P s = leg_points[j];
      auto or0 = CGAL::orientation(*p0, *p1, s);
      auto or1 = CGAL::orientation(*p1, *p2, s);
      auto or2 = CGAL::orientation(*p2, *p0, s);
      covers_leg[j] = (or0 <= 0 && or1 <= 0 && or2 <= 0)
                    || (or0 >= 0 && or1 >= 0 && or2 >= 0);
    }
    for(int j = 0; j < m - 1; j++) { // legs only covered if both j and j+1 covered
      if(covers_leg[j] && covers_leg[j+1]) triang_covers_leg[i].push_back(j);
    }
  }
  vector<int> is_covered(m - 1, 0);
  bool all_covered;
  int min_k = n;
  int e = 1, b = 0;
  for(int k : triang_covers_leg[b]) {
    is_covered[k]++;
  }
  
  while(true) {
    all_covered = true;
    for(int j = 0; j < m - 1; j++) {
      all_covered = all_covered && (is_covered[j] > 0);
    }
    if(all_covered) {
      min_k = min(min_k, e - b);
      for(int k : triang_covers_leg[b]) {
        is_covered[k]--; // do not cover legs of b anymore
      }
      b++;
      if(b == n) break;
    } else {
      e++;
      if(e == n + 1) break;
      for(int k : triang_covers_leg[e - 1]) {
        is_covered[k]++; // now cover additional legs by e-1
      }
    }
    if(e == b) {
      e++;
      for(int k : triang_covers_leg[e - 1]) {
        is_covered[k]++; // do not cover legs of b anymore
      }
    }
  }
  
  cout << min_k << endl;
}
int main()
{
  ios_base::sync_with_stdio(false);
  int c; std::cin >> c;
  for(int i = 0; i < c; ++i) {
    testcase();
  }
}
