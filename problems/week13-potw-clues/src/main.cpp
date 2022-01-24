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

void testcase() {
  Index n, m, r;
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
  
  
  // typedef Triangulation::Vertex_handle Vertex;
  // std::vector<int> freq_assigned(n, -1);
  
  
  bool without_interference = true;
  // for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) {
  //   Index i = v->info();
  //   if(!without_interference) {
  //     break; // already found counterexample
  //   }
  //   // perform BFS until we are not close enough anymore
  //   std::queue<Vertex> Q; // BFS queue (from std:: not boost::)
  //   if(freq_assigned[i] == -1) { // not visited yet, start DFS
  //     freq_assigned[i] = 0;
  //     Q.push(v);
  //     auto point_v = v->point();
  //     while (!Q.empty()) {
  //       const Vertex u = Q.front();
  //       Q.pop();
  //       auto point_u = u->point();
  //       // find all infinite edges incident to v
  //       Triangulation::Vertex_circulator c = t.incident_vertices(u);
  //       do {
  //           if (!t.is_infinite(c)) { 
  //             auto point_c = c->point();
  //             if(CGAL::squared_distance(point_v, point_c) <= r * r) {
                
                
  //               if(CGAL::squared_distance(point_u, point_c) <= r * r) {
                  
  //               }
  //             }
  //           }
  //       } while (++c != t.incident_edges(v));
        
  //     }
  //   } else {
      
  //   }
  // }
  
  if(!without_interference) {
    for(Index i = 0; i < m; i++) {
      std::cout << "n";
    }
    std::cout << std::endl;
    return;
  } 
  // else {
  //   // TODO get rid of this for testcase 2-4
  //   std::cout << "y" << std::endl;
  //   return;
  // }
  
  
  // extract edges and sort by (squared) length
  // This step takes O(n log n) time (for the sorting).
  
  graph G(n);
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    // ensure smaller index comes first
    if (i1 > i2) std::swap(i1, i2);
    if(t.segment(e).squared_length() <= r * r) {
      boost::add_edge(int(i1), int(i2), G);
    }
    // edges.emplace_back(i1, i2, );
  }
  
  for(Index i = 0; i < m; i++) {
    int a0, a1, b0, b1;
    std::cin >> a0 >> a1 >> b0 >> b1;
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
    std::vector<bool> vis(n, false); // visited flags
    std::queue<Index> Q; // BFS queue (from std:: not boost::)
    vis[va] = true; // start from pos balance node
    Q.push(va);
    bool found = false;
    while (!Q.empty()) {
      if(found) break;
      
      const int u = Q.front();
      Q.pop();
      out_edge_it ebeg, eend;
      for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
        const int v = boost::target(*ebeg, G);
        if(v == vb) {
          std::cout << "y";
          found = true;
          break;
        }
        if(vis[v]) continue;
        vis[v] = true;
        Q.push(v);
      }
    }
    if(!found) std::cout << "n";
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
