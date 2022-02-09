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
    
    int left, bottom, right, top;
    cin >> left >> bottom >> right >> top;
    
    // then we build the Delaunay triangulation in one shot, so as to leave the
    // choice of an efficient insertion order to the triangulation structure. By
    // giving the points paired with the indices, these indices are used to
    // initialize the vertex info accordingly.
    // This step takes O(n log n) time (for constructing the triangulation).
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
    
    vector<double> min_distances;
    min_distances.reserve(n);
  
    for(auto vertex = t.finite_vertices_begin(); vertex != t.finite_vertices_end(); ++vertex){
      double x = vertex->point().x();
      double y = vertex->point().y();
      double die_distance = std::min({std::abs(left-x), std::abs(right-x), std::abs(top-y), std::abs(bottom-y)});
  
      double closest_squared_die_distance = numeric_limits<double>::max();
      auto edge_c = t.incident_edges(vertex);
      if(edge_c != 0) {
        do {
          if (!t.is_infinite(edge_c)) {
            closest_squared_die_distance = std::min(closest_squared_die_distance, t.segment(edge_c).squared_length());
          }
        } while (++edge_c != t.incident_edges(vertex));
      }
      min_distances.push_back(std::min(die_distance-0.5, (sqrt(closest_squared_die_distance) - 1)/2));
    }
  
    const int mid_point = n/2;
    std::nth_element(min_distances.begin(), min_distances.begin() + mid_point, min_distances.end());
  

    double first_to_die = sqrt(*std::min_element(std::begin(min_distances), std::begin(min_distances)+mid_point+1));
    double half_dead = sqrt(min_distances[mid_point]);
    double last_to_die = sqrt(*std::max_element(std::begin(min_distances)+mid_point, std::end(min_distances)));
  
    cout << ceil(first_to_die) << " " << ceil(half_dead) << " "<< ceil(last_to_die) << endl;
      
  }
}
