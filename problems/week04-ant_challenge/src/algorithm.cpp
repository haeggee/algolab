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

int dijkstra(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

void kruskal(const weighted_graph &G, vector<edge_desc> &mst) {
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
}


void testcase() {
  int n; cin >> n;
  int m; cin >> m;
  int s; cin >> s;
  int a, b; cin >> a; cin >> b;
  vector<weighted_graph> Gs(s, weighted_graph(n));
  weighted_graph G(n);
  vector<weight_map> weights(s);

  for(int i = 0; i < s; i++)
    weights[i] = boost::get(boost::edge_weight, Gs[i]);
  
  weight_map weights_g = boost::get(boost::edge_weight, G);
  edge_desc e;
  for(int i = 0; i < m; i++) {
    int u,v; cin >> u; cin >> v;
    for(int j = 0; j < s; j++) {
      int w; cin >> w;
      e = boost::add_edge(u, v, Gs[j]).first; weights[j][e] = w;
    }
  }
  
  int hive; // disregard hives
  for(int i = 0; i < s; i++) {
    cin >> hive;
  }
  for(int i = 0; i < s; i++) {
    vector<edge_desc> mst;
    kruskal(Gs[i], mst);
    for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
        int u = boost::source(*it, Gs[i]);
        int v = boost::target(*it, Gs[i]);
        if(!edge(u,v,G).second) { // edge not yet in G
          e = boost::add_edge(u, v, G).first;
          weights_g[e] = weights[i][*it];
        } else {
          e = edge(u,v,G).first;
          weights_g[e] = min(weights_g[e], weights[i][*it]);
        }
    }
  }
  
  cout << dijkstra(G, a, b) << endl;
  
}
int main()
{
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  return 0;
}
