// STL includes
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>


using namespace std;

struct topological {
  bool operator() (const pair<int, int> t0, const pair<int, int> t1) {
    return (t0.first < t1.first) || (t0.first == t1.first && t0.second < t1.second);
  }
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      graph;
typedef boost::property_map<graph, boost::edge_weight_t>::type edge_map;
typedef boost::graph_traits<graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor          vertex_desc;
typedef boost::graph_traits<graph>::edge_iterator                         edge_it;

void important_bridges(graph &G) {
  edge_map component = boost::get(boost::edge_weight, G);
  int ncc = boost::biconnected_components(G, component); 
  
  vector<pair<int, int>> imp_bridges(0); 
  edge_it ebeg, eend;
  vector<int> size_ncc(ncc, 0);
  for (boost::tie(ebeg, eend) = boost::edges(G); ebeg != eend; ++ebeg) {
    size_ncc[component[*ebeg]]++;
  }
  
  for (boost::tie(ebeg, eend) = boost::edges(G); ebeg != eend; ++ebeg) {
    int u = boost::source(*ebeg, G), v = boost::target(*ebeg, G);
    if (size_ncc[component[*ebeg]] == 1) imp_bridges.push_back({min(u,v),max(u,v)});
  }
  std::sort(imp_bridges.begin(), imp_bridges.end(), topological());
  cout << imp_bridges.size() << endl;
  for(auto e : imp_bridges)
    cout << e.first <<  " " << e.second << endl;
  
}

void testcase()
{
  int n; cin >> n;
  int m; cin >> m;
  graph G(n);
  for(int i = 0; i < m; i++) {
    int e1, e2; cin >> e1; cin >> e2;
    boost::add_edge(e1, e2, G);
  }
  
  important_bridges(G);
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  while(t--) testcase();
}
