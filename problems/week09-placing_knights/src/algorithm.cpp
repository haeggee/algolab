///3
// ALGOLAB BGL Tutorial 3
// Flow example demonstrating
// - breadth first search (BFS) on the residual graph

// Compile and run with one of the following:
// g++ -std=c++11 -O2 bgl_residual_bfs.cpp -o bgl_residual_bfs ./bgl_residual_bfs
// g++ -std=c++11 -O2 -I path/to/boost_1_58_0 bgl_residual_bfs.cpp -o bgl_residual_bfs; ./bgl_residual_bfs

// Includes
// ========
// STL includes
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

// BGL graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef  boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
  boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
      boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >  graph;
// Interior Property Maps
typedef traits::vertex_descriptor vertex_desc;

typedef  boost::graph_traits<graph>::edge_descriptor      edge_desc;
typedef  boost::graph_traits<graph>::out_edge_iterator      out_edge_it;

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};


void add_if_present(edge_adder & adder, std::vector<int> &present, int n, int u, int i, int j, int c) {
  if(i >= 0 && j >= 0 && i <= (n-1) && j <= (n-1)) {
    if(present[i * n + j]) {
      adder.add_edge(u, i * n + j, c);
    }
  }
}

// Main
void testcase() {
  // build graph
  int n;
  std::cin >> n;
  graph G(n * n);
  edge_adder adder(G);
  // auto rc_map = boost::get(boost::edge_residual_capacity, G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  std::vector<int> present(n*n);
  
  int sum_present = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      std::cin >> present[i * n + j];
      if(present[i * n + j]) {
        sum_present++;
        if((i + j) % 2 == 0)
          adder.add_edge(v_source, i * n + j, 1);
        else
          adder.add_edge(i * n + j, v_sink, 1);
      }
    }
  }
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      int ij = i * n + j;
      if(present[ij] && (i + j) % 2 == 0) {
        add_if_present(adder, present, n, ij, (i - 1), j - 2, 1);
        add_if_present(adder, present, n, ij, (i - 1), j + 2, 1);
        add_if_present(adder, present, n, ij, (i + 1), j - 2, 1);
        add_if_present(adder, present, n, ij, (i + 1), j + 2, 1);
        add_if_present(adder, present, n, ij, (i - 2), j - 1, 1);
        add_if_present(adder, present, n, ij, (i - 2), j + 1, 1);
        add_if_present(adder, present, n, ij, (i + 2), j - 1, 1);
        add_if_present(adder, present, n, ij, (i + 2), j + 1, 1);
      //   if(i > 0 && j > 1)
      //     adder.add_edge(ij, (i - 1) * n + j - 2, 1);
      //   if(i > 0 && j < (n - 2))
      //     adder.add_edge(ij, (i - 1) * n + j + 2, 1);
      //   if(i < (n - 1) && j > 1)
      //     adder.add_edge(ij, (i + 1) * n + j - 2, 1);
      //   if(i < (n - 1) && j < (n - 2))
      //     adder.add_edge(ij, (i + 1) * n + j + 2, 1);
      //   if(i > 1 && j > 0)
      //     adder.add_edge(ij, (i - 2) * n + j - 1, 1);
      //   if(i > 1 && j < (n - 1))
      //     adder.add_edge(ij, (i - 2) * n + j + 1, 1);
      //   if(i < (n - 2) && j > 0)
      //     adder.add_edge(ij, (i + 2) * n + j - 1, 1);
      //   if(i < (n - 2) && j < (n - 1))
      //     adder.add_edge(ij, (i + 2) * n + j + 1, 1);
      }
    }
  }
  
  // for(int i = 0; i < n; i++) {
  //   // adder.add_edge(v_source, i, 1);
  //   adder.add_edge(i, v_sink,  std::numeric_limits<int>::max());
  // }
  
  int flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  // auto c_map = boost::get(boost::edge_capacity, G);
  // auto rc_map = boost::get(boost::edge_residual_capacity, G);
  // Find a min cut via maxflow
  std::cout << sum_present - flow << "\n";
  // std::cerr << std::endl;
  // // Retrieve the capacity map and reverse capacity map
  // const auto c_map = boost::get(boost::edge_capacity, G);
  // const auto rc_map = boost::get(boost::edge_residual_capacity, G);

  // // Iterate over all the edges to print the flow along them
  // auto edge_iters = boost::edges(G);
  // for (auto edge_it = edge_iters.first; edge_it != edge_iters.second; ++edge_it) {
  //   const edge_desc edge = *edge_it;
  //   const long flow_through_edge = c_map[edge] - rc_map[edge];
  //   std::cerr << "edge from " << boost::source(edge, G) << " to " << boost::target(edge, G)
  //             << " runs " << flow_through_edge
  //             << " units of flow (negative for reverse direction). \n";
  // }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t t;
  for (std::cin >> t; t > 0; --t) testcase();
  return 0;
}
