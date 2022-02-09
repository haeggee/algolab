// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

using namespace std;

int furthest_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
  
  int max_dist = 0;
  for(int i = 1; i < n; i++) {
    if(dist_map[i] > max_dist) 
      max_dist = dist_map[i];
  }
  return max_dist;
}

int span_tree_weight(const weighted_graph &G, const weight_map &weights) {
  std::vector<edge_desc> mst;    // vector to store MST edges (not a property map!)

  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  int total_weight = 0;
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    total_weight += weights[*it];
  }
  return total_weight;
}


void testcase() {
  int n; cin >> n;
  int m; cin >> m;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;
  for(int i = 0; i < m; i++) {
    int u,v; cin >> u; cin >> v;
    int w; cin >> w;
    e = boost::add_edge(u, v, G).first; weights[e] = w;
  }
  
  cout << span_tree_weight(G, weights) << " ";
  cout << furthest_dist(G, 0) << endl;
  
}
int main()
{
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  return 0;
}
