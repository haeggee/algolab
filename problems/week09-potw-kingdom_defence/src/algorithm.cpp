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
  int l, p;
  cin >> l; cin >> p;
  graph G(l);
  edge_adder adder(G);
  // Add special vertices source and sink
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  
  vector<int> supply(l);
  vector<int> demand(l);
  int sum_demands = 0;
  int sum_supply = 0;
  for(int i = 0; i < l; i++) {
    cin >> supply[i];
    cin >> demand[i];
    sum_supply += supply[i];
  }
  
  for(int i = 0; i < p; i++) {
    int u, v; cin >> u; cin >> v;
    int min_c, max_c; cin >> min_c; cin >> max_c;
    demand[u] += min_c;
    supply[v] += min_c;
    adder.add_edge(u, v, max_c - min_c); // from, to, capacity
  }
  
  for(int i = 0; i < l; i++) {
    if(demand[i] > supply[i]) {
      sum_demands += demand[i] - supply[i];
      adder.add_edge(i, v_sink, demand[i] - supply[i]); 
    }
    if(supply[i] > demand[i]) {
      adder.add_edge(v_source, i, supply[i] - demand[i]);
    }
  }
  
  // Calculate flow from source to sink
  // The flow algorithm uses the interior properties (managed in the edge adder)
  // - edge_capacity, edge_reverse (read access),
  // - edge_residual_capacity (read and write access).
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  if(flow == sum_demands) {
    std::cout << "yes" << "\n";
  } else {
    std::cout << "no" << "\n";
  }
  
  // Retrieve the capacity map and reverse capacity map
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
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  while(t--) make_it_flow();
  return 0;
}
