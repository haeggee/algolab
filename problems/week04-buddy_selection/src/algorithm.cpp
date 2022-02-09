// STL includes
#include <iostream>
#include <vector>
#include <unordered_set>
#include <climits>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/maximum_weighted_matching.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

using namespace std;


int maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc> mate_map(n);  // exterior property map
  // const vertex_desc NULL_VERTEX = boost::graph_traits<weighted_graph>::null_vertex();

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  return matching_size;
  // int min_weight = INT_MAX;
  // edge_desc e;
  // for (int i = 0; i < n; ++i) {
  //   // mate_map[i] != NULL_VERTEX: the vertex is matched
  //   // i < mate_map[i]: visit each edge in the matching only once
  //   // cout << i << " " << mate_map[i] << endl;
  //   e = edge(i,mate_map[i],G).first;
  //   min_weight = min(min_weight, weights[e]);
  // }
  // return min_weight;
}

void testcase()
{
  int n; cin >> n;
  int c; cin >> c;
  int f; cin >> f;
  graph G(n);
  vector<unordered_set<string>> characteristics(n);
  for(int i = 0; i < n; i++) {
    characteristics[i] = unordered_set<string>(0);
    for(int k = 0; k < c; k++) {
      string s; cin >> s;
      characteristics[i].insert(s);
    }
    for(int j = 0; j < i; j++) {
      int common = 0;
      for(auto s : characteristics[j]) {
        if(characteristics[i].count(s) > 0) common++;
      }
      // cout << i << " " << j << " " << common << " ";
      if(common > f) {
        // cout << i << " " << j << endl;
        boost::add_edge(i, j, G);
      }
      // cout << e << " " << weights[e] << endl;
    }
  }
  
  int matching_size = maximum_matching(G);
  // std::cout << matching_size << endl;
  if(matching_size == n / 2) {
    cout << "not optimal" << endl;
  } else {
    cout << "optimal" << endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  while(t--) testcase();
}
