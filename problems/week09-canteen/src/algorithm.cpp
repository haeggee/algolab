///
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

// BGL graph definitions
// =====================
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
  int n;
  std::cin >> n;
  graph G(n);
  edge_adder adder(G);
  // auto rc_map = boost::get(boost::edge_residual_capacity, G);
  const int v_source = boost::add_vertex(G);
  const int v_sink = boost::add_vertex(G);
  
  
  std::vector<int> a_and_c(2*n);
  for(int i = 0; i < n; i++) {
    int a, c;
    std::cin >> a >> c;
    a_and_c[2 * i] = a;
    a_and_c[2 * i + 1] = c;
    // adder.add_edge(v_source, i, a, c);
  }
  
  int sum_students = 0;
  int max_price = 0;
  std::vector<int> s_and_p(2*n);
  for(int i = 0; i < n; i++) {
    int s, p;
    std::cin >> s >> p;
    sum_students += s;
    s_and_p[2 * i] = s;
    s_and_p[2 * i + 1] = p;
    max_price = std::max(max_price, p);
  }
  
  for(int i = 0; i < n; i++) {
    int a = a_and_c[2 * i];
    int c = a_and_c[2 * i + 1];
    adder.add_edge(v_source, i, a, c);
  }
  
  for(int i = 0; i < n; i++) {
    int s = s_and_p[2 * i];
    int p = s_and_p[2 * i + 1];
    adder.add_edge(i, v_sink, s, - p + max_price);
  }
  
  for(int i = 0; i < n - 1; i++) {
    int v, e;
    std::cin >> v >> e;
    adder.add_edge(i, i + 1, v, e);
  }

  
  // int flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  // boost::cycle_canceling(G);
  // int cost = boost::find_flow_cost(G);
  
  
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
  int cost = boost::find_flow_cost(G);
  // Iterate over all edges leaving the source to sum up the flow values.
  int flow = 0;
  out_edge_it e, eend;
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);  
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
      // std::cout << "edge from " << boost::source(*e, G) << " to " << boost::target(*e, G) 
      //     << " with capacity " << c_map[*e] << " and residual capacity " << rc_map[*e] << "\n";
      flow += c_map[*e] - rc_map[*e];     
  }
  if(flow == sum_students) {
    std::cout << "possible ";
  } else {
    std::cout << "impossible ";
  }
  std::cerr << flow * max_price << std::endl;
  std::cout << flow << " " << -(cost - (flow * max_price)) << "\n";
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
