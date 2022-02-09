///2
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

using namespace std;

int main()
{
  // read number of points
  size_t n;
  while(true){
    cin >> n;
    if(n == 0) {
      return 0;
    }
    // read points
    vector<K::Point_2> pts;
    pts.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
      int x, y;
      cin >> x >> y;
      pts.push_back(K::Point_2(x, y));
    }
    // construct triangulation
    Triangulation t;
    t.insert(pts.begin(), pts.end());
    int m; cin >> m;
    // output all edges
    for (int j = 0; j < m; j++) {
      int x, y; cin >> x >> y;
      K::Point_2 q = K::Point_2(x, y);
      Triangulation::Vertex_handle v = t.nearest_vertex(q);
      K::Point_2 p = v->point();
      cout << long(CGAL::squared_distance(p, q)) << endl;
    }
      
  }
}
