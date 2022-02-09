//
// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

int dijkstra(const weighted_graph &G, int s, int k) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
  int min_dist = dist_map[0];
  for(int i = 1; i < k; i++) {
    min_dist = min(min_dist, dist_map[i]);
  }
  return min_dist;
}


void testcase() {
  int n; cin >> n;
  int m; cin >> m;
  int k; cin >> k;
  int T; cin >> T;
  vector<int> tele_nodes(T);
  for(int i = 0; i < T; i++) {
    cin >> tele_nodes[i];
  }
  weighted_graph G(n);
  
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;
  for(int i = 0; i < m; i++) {
    int u,v; cin >> u; cin >> v;
    int c; cin >> c;
    e = boost::add_edge(v, u, G).first; weights[e] = c; // flipped edges!
  }
  // scc_map[i]: index of SCC containing i-th vertex
  vector<int> scc_map(n); // exterior property map
  // nscc: total number of SCCs
  int nscc = boost::strong_components(G,
      boost::make_iterator_property_map(scc_map.begin(),
      boost::get(boost::vertex_index, G)));
  
  vector<int> size_scc(nscc);
  for(int i = 0; i < T; i++) {
    size_scc[scc_map[tele_nodes[i]]]++;
  }
  
  
  for(int i = 0; i < T; i++) {
      int u = tele_nodes[i];
      int scc = scc_map[u];
      int size_this_scc = size_scc[scc] - 1;
      e = boost::add_edge(u, n + scc, G).first;
      weights[e] = size_this_scc;
      e = boost::add_edge(n + scc, u, G).first;
      weights[e] = 0;
  }
  
  int min_dist_to_warehouse = dijkstra(G, n - 1, k);
  if(min_dist_to_warehouse <= 1e6) {
    cout << min_dist_to_warehouse << endl;
  } else {
    cout << "no" << endl;
  }
  
}
int main()
{
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  return 0;
}
