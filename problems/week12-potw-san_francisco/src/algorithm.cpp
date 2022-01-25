///3
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
// BGL graph definitions
// =====================
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, long> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
typedef  boost::graph_traits<weighted_graph>::out_edge_iterator      out_edge_it;

// Main
void testcase() {
  // build graph
  long n, m, x, k;
  std::cin >> n >> m >> x >> k;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  edge_desc e;
  
  std::vector<int> num_outgoing(n, 0);
  
  for(int i = 0; i < m; i++) {
    long u, v, p;
    std::cin >> u >> v>> p;
    e = boost::add_edge(u, v, G).first; weights[e]=p;
    num_outgoing[u] += 1;
  }
  
  std::vector<std::vector<long>> maxpoints_after(k + 1);
  for(int i = 0; i <= k; i++) {
    maxpoints_after[i] = std::vector<long>(n, 0);
  }

  out_edge_it ebeg, eend;
  for(int j = 0; j < k; j++) {
    for(int i = 0; i < n; i++) {
      long maxpoints = 0;
      for (boost::tie(ebeg, eend) = boost::out_edges(i, G); ebeg != eend; ++ebeg) {
        const int v = boost::target(*ebeg, G);
        const long pi = weights[*ebeg];
        maxpoints = std::max(maxpoints, maxpoints_after[j][v] + pi);
        if(i == 0 && maxpoints >= x) {
          std::cout << j + 1 << std::endl;
          return;
        }
      }
      if(num_outgoing[i] == 0) {
        maxpoints_after[j + 1][i] = maxpoints_after[j + 1][0];
      } else {
        maxpoints_after[j + 1][i] = maxpoints;
      }
    }
  }
  std::cout << "Impossible" << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t t;
  for (std::cin >> t; t > 0; --t) testcase();
  return 0;
}