/* Tags: Minimal Spanning Tree, DFS, 2nd MST

  Key idea: * we look for 2nd best MST
            * construct MST with Kruskal
              --> Leias solution (equivalent to her Prim algorithm in terms of weight)
            * compute max edge on pairwise paths in MST with DFS in O(n^2) (paths are unique in tree)
            * loop through all edges _not_ in MST and
              compute best differences in adding edge (u,v) and
              removing worst edge on MST path between u and v
            * WHY? 2nd best MST is attained by adding a single edge that previosuly wasnt in MST
                   and then deleting the largest edge in the cycle that is introduced.
            * Since the graph is fully connected here, it is more efficient to 
              precompute pairwise max_edge_weights in O(n^2) than to do it for each 
              edge in O(E * V)
*/

// STL includes
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/pending/disjoint_sets.hpp>

typedef std::size_t                                            Index;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
// edge: (u,v,c)
typedef std::tuple<int,int,int> Edge;
typedef std::vector<Edge> EdgeV;

void testcase()
{
  int n, tatt;
  std::cin >> n >> tatt;
  EdgeV edges;
  edges.reserve(n*n);
  for(int i = 0; i < n - 1; i++) {
      for(int j = 0; j < n - i - 1; j++) {
            int c;
            std::cin >> c;
            edges.emplace_back(i, i + j + 1, c);
      }
  }

  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });
  
  // construct MST with Kruskal --> Leias solution (equivalent to her Prim algorithm)
  std::vector<std::vector<int>> edge_in_mst(n, std::vector<int>(n, 0)); // nonzero means included
  boost::disjoint_sets_with_storage<> uf(n);
  int mst_cost = 0;
  int n_components = n;
  std::vector<std::vector<int>> mst_edges(n, std::vector<int>(0));
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    Index i1 = std::get<0>(*e);
    Index i2 = std::get<1>(*e);
    Index c1 = uf.find_set(i1);
    Index c2 = uf.find_set(i2);
    int cost = std::get<2>(*e);
    if(c1 != c2) {
      mst_cost += cost;
      uf.link(c1, c2);
      edge_in_mst[i1][i2] = cost;
      edge_in_mst[i2][i1] = cost;
      mst_edges[i1].push_back(i2);
      mst_edges[i2].push_back(i1);
      if(--n_components == 1) break;
    }
  }
 
  // compute max edge on pairwise paths in MST with DFS
  std::vector<std::vector<int>> max_e_betw(n, std::vector<int>(n, 0));
  for(int i = 0; i < n; i++) {
      std::stack<std::pair<int,int>> Q; // pair of (node, max edge on path form i to node)
      Q.push({i,0});
      std::vector<bool> visited(n, false);
      while(!Q.empty()) {
        auto v = Q.top();
        int j = v.first; int c = v.second;
        Q.pop();
        if(!visited[j]) {
          visited[j] = true;
          max_e_betw[i][j] = c;
          for(auto k : mst_edges[j]) Q.push({k, std::max(c, edge_in_mst[j][k])});
        }
      }
  }
  
  // loop through all edges not in MST, compute best differences in adding edge (u,v) and
  // removing worst edge on MST path between u and v
  int min_diff = std::numeric_limits<int>::max();
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    Index i1 = std::get<0>(*e);
    Index i2 = std::get<1>(*e);
    int cost = std::get<2>(*e);
    if(edge_in_mst[i1][i2] == 0) {
        min_diff = std::min(min_diff, cost - max_e_betw[i1][i2]);
    }
  }

  std::cout << mst_cost + min_diff << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
