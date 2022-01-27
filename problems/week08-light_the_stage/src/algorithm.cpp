/*
Tags: Binary Search, Delaunay Triangulation, Nearest Neighbor

Key idea: 
  * We have the invariant that if a participant is out after lights [0,i], he will also be out after [0,k] for k >= i.
  * It doesn't matter what round a participant got out, we only care about the _last_ round that participants survived
  * Hence, let's save for each participant the _lowest_ number of rounds that we found where we know for sure that he's out
  * Then, search to find the _lowest_ round i s.t. no one survived rounds [0,i]. Do binary search:
    * Start with interval [0,n-1]: for interval [l,r] and midpoint mid=(l+r)/2, compute Delaunay triangulation for lights [l,mid] (We need this in order to find nearest light for each participant in log(n) time)
    * For each participant, check if he will be out by those lights by checking if the nearest light is < (h+r)^2 away -> if he is out, store mid as his lowest known round to be out
    * If no participant survived, then we know the lowest round i is smaller than mid; set r to mid
    * else, set l = mid + 1
  * At the end, look for the maximum round stored for the participants, and print out those with same number

Note: Asymptotically, it does not make a difference to compute the triangulation between [0,mid] or [l,mid], but I got a timeout for the former one!
*/

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
  vector<IPoint> pts;
  pts.reserve(n);
  for (std::size_t i = 0; i < m; ++i) {
    int x, y, r;
    cin >> x >> y >> r;
    pts.emplace_back(K::Point_2(x, y), r);
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
  std::vector<size_t> out_after_rounds(m, numeric_limits<size_t>::max());

  // binary search
  while(l <= r) {
    size_t mid = (l + r) / 2;
    Triangulation t;
    t.insert(lights.begin() + l, lights.begin() + mid + 1);
    int pts_left = m;
    for(size_t k = 0; k < m; k++) {
        if(out_after_rounds[k] < mid) {
            pts_left--;
            continue;
        }
        auto p = pts[k].first;
        auto r = pts[k].second;
        auto v = t.nearest_vertex(p);
        K::FT distance = CGAL::squared_distance(p, v->point());
        K::FT hr = h + r;
        if(distance < hr * hr) { // not <=, as area has to be positive
            out_after_rounds[k] = min(out_after_rounds[k], mid);
            pts_left--;
        }
    }

    if(pts_left == 0) {
      r = mid;
      if(l == r) break;
    } else {
      l = mid + 1;
    }
  }

  size_t last_game = *max_element(out_after_rounds.begin(), out_after_rounds.end());
  for(size_t i = 0; i < m; i++) {
    if(out_after_rounds[i] == last_game) {
      cout << i << " ";
    }
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
