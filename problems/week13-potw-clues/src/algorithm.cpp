///2
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <vector>
#include <iostream>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/bipartite.hpp>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS    // Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
    >          graph;
typedef boost::graph_traits<graph>::vertex_descriptor    vertex_desc;    // Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).  
typedef boost::graph_traits<graph>::edge_iterator    edge_it;    // to iterate over all edges
typedef  boost::graph_traits<graph>::out_edge_iterator      out_edge_it;
// Coloring definitions
typedef std::vector< boost::default_color_type > partition_t;



void testcase() {
  Index n, m;
  double r;
  std::cin >> n >> m >> r;
  
  // read points: first, we read all points and store them into a vector,
  // together with their indices
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  
  Delaunay t;
  t.insert(points.begin(), points.end());
  
  graph G(n);
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if(t.segment(e).squared_length() <= r * r) {
      boost::add_edge(int(i1), int(i2), G);
    }
  }
   
  // check for bipartiteness of the graph with *only* the delaunay edges
  partition_t partition(n); 
  bool without_interference = boost::is_bipartite(G, boost::get(boost::vertex_index, G), 
        boost::make_iterator_property_map(partition.begin(), boost::get(boost::vertex_index, G)));
  if(without_interference) {
    // if bipartite only with delaunay edges, we can use the coloring found by BGL
    // to create one triangulation for each color. Since same colored points should
    // not be closer than r to each other, this new triangulation should not include small edges  
    std::vector<K::Point_2> points_1;
    std::vector<K::Point_2> points_2;
    for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) {
        Index i = v->info();
        if(partition[i] == boost::color_traits<boost::default_color_type>::white()) {
            points_1.push_back(v->point());
        } else {
            points_2.push_back(v->point());
        }
    }

    for(int i = 0; i < 2; i++) {
        if(!without_interference) break;
        Delaunay ti;
        if(i == 0) ti.insert(points_1.begin(), points_1.end());
        else ti.insert(points_2.begin(), points_2.end());
        // loop through edges
        for (auto e = ti.finite_edges_begin(); e != ti.finite_edges_end(); ++e) {
            if(t.segment(e).squared_length() <= r * r) {
                without_interference = false;
                break;
            }
        }
    }
  }
  
  
  std::vector<int> component_map(n);	// We MUST use such a vector as an Exterior Property Map: Vertex -> Component
  boost::connected_components(G,
        boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 


  for(Index i = 0; i < m; i++) {
    int a0, a1, b0, b1;
    std::cin >> a0 >> a1 >> b0 >> b1;
    if(!without_interference) {
        std::cout << "n";
        continue;
    }
    K::Point_2 a = K::Point_2(a0, a1);
    K::Point_2 b = K::Point_2(b0, b1);
    
    if(CGAL::squared_distance(a, b) <= r * r) {
      std::cout << "y";
      continue;
    }
    auto vertex_a = t.nearest_vertex(a);
    auto vertex_b = t.nearest_vertex(b);
    
    if(CGAL::squared_distance(a, vertex_a->point()) > r * r || CGAL::squared_distance(b, vertex_b->point()) > r * r) {
        std::cout << "n";
        continue;
    }
    
    int va = vertex_a->info();
    int vb = vertex_b->info();
    if(component_map[va] == component_map[vb]) {
        std::cout << "y";
        continue;
    } else {
        std::cout << "n";
        continue;
    }
  }
  
  std::cout << "\n";
  
}

int main() 
{
  std::ios_base::sync_with_stdio(false);
  std::size_t t;
  for (std::cin >> t; t > 0; --t) testcase();
  return 0;
}
