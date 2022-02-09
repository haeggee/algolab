#include <iostream>
#include <climits>
// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

using namespace std;


int c_to_i (char c) {
  return c - 'A';
}
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
  int h, w;
  cin >> h; cin >> w;
  string note; cin >> note;
  int n = note.length();
  graph G(26 * 26 + 26);
  edge_adder adder(G);
  // Add special vertices source and sink
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);

  vector<int> char_count(26, 0);
  for(int i = 0; i < n; i++) {
    char c = note[i];
    char_count[c_to_i(c)]++;
  }
  
  vector<int> pair_count(26*26, 0);
  vector<string> front(h);
  for(int i = 0; i < h; i++) {
    string line; cin >> line;
    front[i] = line;  
    // for(int j = 0; j < w; j++) {
    //   char c = line[j];
    //   adder.add_edge(i * w + j, h * w + c_to_i(c), 1);
    // }
  }
  vector<string> back(h);
  for(int i = 0; i < h; i++) {
    string line; cin >> line;
    back[i] = line;
    // for(int j = w - 1; j >= 0; j--) {
    //   char c = line[w - j - 1];
    //   adder.add_edge(i * w + j, h * w + c_to_i(c), 1);
    // }
  }
  
  for(int i = 0; i < h; i++) {
    string line_front = front[i];
    string line_back = back[i];
    for(int j = 0; j < w; j++) {
      char c_front = line_front[j];
      char c_back = line_back[w - j - 1];
      int i_front = c_to_i(c_front);
      int i_back = c_to_i(c_back);
      pair_count[i_front * 26 + i_back]++;
    }
  }
  
  for(int i = 0; i < 26; i++) {
    for(int j = 0; j < 26; j++) {
      adder.add_edge(i * 26 + j, 26 * 26 + i, INT_MAX);
      adder.add_edge(i * 26 + j, 26 * 26 + j, INT_MAX);
    }
  }
  
  for(int i = 0; i < 26 * 26; i++) {
    adder.add_edge(v_source, i, pair_count[i]);
  }
  
  
  for(int i = 0; i < 26; i++) {
    adder.add_edge(26 * 26 + i, v_sink, char_count[i]);
  }
  
  // Calculate flow from source to sink
  // The flow algorithm uses the interior properties (managed in the edge adder)
  // - edge_capacity, edge_reverse (read access),
  // - edge_residual_capacity (read and write access).
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  if(flow == n) {
    std::cout << "Yes" << "\n";
  } else {
    std::cout << "No" << "\n";
  }
  
  
  // Retrieve the capacity map and reverse capacity map
  // const auto c_map = boost::get(boost::edge_capacity, G);
  // const auto rc_map = boost::get(boost::edge_residual_capacity, G);

  // Iterate over all the edges to print the flow along them
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
  while(t--) {
    // cerr << "-----------------testcase done" << endl;
    make_it_flow();
  }
  return 0;
}
