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
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};


// Main
void testcase() {
  // build graph
  int n, m, s;
  std::cin >> n >> m >> s;
  graph G(n + m + s);
  edge_adder adder(G);
  // auto rc_map = boost::get(boost::edge_residual_capacity, G);
  const int v_source = boost::add_vertex(G);
  const int v_sink = boost::add_vertex(G);
  
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  for(int i = 0; i < s; i++) {
    int l;
    std::cin >> l;
    adder.add_edge(v_source, i, l, 0); // no cost
  }
  
  for(int i = 0; i < m; i++) {
    int si;
    std::cin >> si;
    adder.add_edge(si - 1, s + i, 1, 0); // no cost
  }
  
  std::vector<int> costs(n * m);
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      int bij;
      std::cin >> bij;
      costs[i * m + j] = bij;
      // adder.add_edge(s + j, s + m + i, 1, -bij); // no cost
    }
    adder.add_edge(s + m + i, v_sink, 1, 0); // 1 purchase per buyer, no cost
  }
  
  int max_cost = *std::max_element(costs.begin(), costs.end());
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      int bij = costs[i * m + j];
      adder.add_edge(s + j, s + m + i, 1, -bij + max_cost); // no cost
    }
  }
  
  // Find a min cut via maxflow
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost = boost::find_flow_cost(G);
    
  // Iterate over all edges leaving the source to sum up the flow values.
  int s_flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
      // std::cout << "edge from " << boost::source(*e, G) << " to " << boost::target(*e, G) 
      //     << " with capacity " << c_map[*e] << " and residual capacity " << rc_map[*e] << "\n";
      s_flow += c_map[*e] - rc_map[*e];     
  }
  std::cout << s_flow << " "; // 5
  std::cout << -cost + (s_flow * max_cost) << "\n";

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t t;
  for (std::cin >> t; t > 0; --t) testcase();
  return 0;
}
