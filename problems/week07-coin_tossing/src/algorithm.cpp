// Algolab BGL Tutorial 2 (Max flow, by taubnert@ethz.ch)
// Flow example demonstrating how to use push_relabel_max_flow using a custom edge adder
// to manage the interior graph properties required for flow algorithms
#include <iostream>

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

using namespace std;

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void make_it_flow() {
  int n, m;
  cin >> n; cin >> m;
  graph G(n + m);
  edge_adder adder(G);
  
  // Add special vertices source and sink
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  for(int i = 0; i < m; i++) {
    adder.add_edge(v_source, i, 1); // from, to, capacity
    int a, b, c;
    cin >> a; cin >> b; cin >> c;
    if(c == 1) {
      adder.add_edge(i, m + a, 1); // from, to, capacity  
    } else if(c == 2) {
      adder.add_edge(i, m + b, 1); // from, to, capacity
    } else {
      adder.add_edge(i, m + a, 1); // from, to, capacity
      adder.add_edge(i, m + b, 1); // from, to, capacity
    }
  }

  int sum_s = 0;
  for(int i = 0; i < n; i++) {
    int si; cin >> si;
    adder.add_edge(m + i, v_sink, si);
    sum_s += si;
  }
  

  // Calculate flow from source to sink
  // The flow algorithm uses the interior properties (managed in the edge adder)
  // - edge_capacity, edge_reverse (read access),
  // - edge_residual_capacity (read and write access).
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  if(flow == sum_s && flow == m) {
    std::cout << "yes" << "\n";
  } else {
    std::cout << "no" << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  while(t--) make_it_flow();
  return 0;
}
