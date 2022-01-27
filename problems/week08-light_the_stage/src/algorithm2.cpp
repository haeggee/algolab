// Alternative implementation, a bit more efficient by only
// looping through the leftover participants
#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_data_structure_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<size_t,K> VB;
typedef CGAL::Triangulation_face_base_2<K> FB;
typedef CGAL::Triangulation_data_structure_2<VB,FB> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

void testcase()
{
  // read number of points
  size_t m, n;
  cin >> m >> n;

  typedef pair<K::Point_2,size_t> IPoint;
  vector<pair<IPoint, size_t>> pts;
  pts.reserve(n);
  for (std::size_t i = 0; i < m; ++i) {
    int x, y, r;
    cin >> x >> y >> r;
    pts.emplace_back(IPoint(K::Point_2(x, y), r), i);
  }
  
  size_t h;
  cin >> h;

  vector<IPoint> lights;
  for(size_t j = 0; j < n; j++) {
    int x, y;
    cin >> x >> y;
    lights.emplace_back(K::Point_2(x, y), j);
  }

  size_t l = 0, r = n - 1;
  // binary search
  while(l <= r) {
    // std::cerr << l << " " << r << "\n";
    size_t mid = (l + r) / 2;
    Triangulation t;
    t.insert(lights.begin() + l, lights.begin() + mid + 1);
    vector<pair<IPoint, size_t>> pts_left;
    pts_left.reserve(pts.size());
    for(auto pi : pts) {
        auto p = pi.first.first;
        auto r = pi.first.second;
        auto v = t.nearest_vertex(p);
        K::FT distance = CGAL::squared_distance(p, v->point());
        K::FT hr = h + r;
        if(distance >= hr * hr) { // not >, as area has to be positive
            pts_left.push_back(pi);
        }
    }

    if(pts_left.size() == 0) {
      r = mid;
      if(r == l) break;
    } else {
      l = mid + 1;
      pts = pts_left;
    }
  }

  for(auto p : pts) {
    cout << p.second << " ";
  }
  cout << endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i)
    testcase();
}
