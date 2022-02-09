///

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <iterator>
// BGL includes
// #include <boost/graph/adjacency_list.hpp>

// // BGL graph definitions
// // =====================
// // Graph Type with nested interior edge properties for Flow Algorithms
// // =====================
// // Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
// typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS     // Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
//     >          graph;
// typedef boost::graph_traits<graph>::vertex_descriptor    vertex_desc;    // Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).  
// typedef boost::graph_traits<graph>::edge_iterator    edge_it;    // to iterate over all edges
// typedef  boost::graph_traits<graph>::out_edge_iterator      out_edge_it;
// // Custom Edge Adder Class, that holds the references
// // to the graph, capacity map and reverse edge map
// // ===================================================

std::vector<int> age;
std::vector<int> solution;
std::vector<std::pair<int,int>> curr_path;

struct second_greater {
  bool operator() (const std::pair<int, int>& t0, const std::pair<int,int>& t1) {
    return t0.second > t1.second;
  }
};


void solve_for(int idx, std::vector<std::vector<int>> &children,
  std::vector<std::vector<std::pair<int,int>>> &queries) {
        
  curr_path.push_back({idx, age[idx]});
  std::vector<std::pair<int,int>> queries_for_idx = queries[idx];
  for(auto p : queries_for_idx) {
    int sol_idx = p.first;
    int b = p.second;
    auto j = std::lower_bound(curr_path.begin(), curr_path.end(), std::make_pair(0, b), second_greater());
    solution[sol_idx] = j->first;
  }
  for(const int i : children[idx]) {
    solve_for(i, children, queries);
  }
  
  curr_path.pop_back();
  
}

// Main
void testcase() {
  // build graph
  int n, q;
  std::cin >> n >> q;
  
  std::unordered_map<std::string, int> name_to_ind;
  name_to_ind.clear();
  
  std::vector<std::vector<int>> children(n);
  
  age.clear();
  age.reserve(n);
  
  solution.clear();
  solution = std::vector<int>(q);
  
  curr_path.clear();
  
  std::vector<std::string> ind_to_name;
  ind_to_name.reserve(n);
  
  
  int root = -1;
  int max_age =  std::numeric_limits<int>::min();
  
  for(int i = 0; i < n; i++) {
    std::string s; int a;
    std::cin >> s; std::cin >> a;
    name_to_ind.insert({s, i});
    ind_to_name.push_back(s);
    age.push_back(a);
    if(a > max_age) {
      root = i; max_age = a;
    }
  }
  
  for(int i = 0; i < n - 1; i++) {
    std::string s, p;
    std::cin >> s; std::cin >> p;
    children[name_to_ind.at(p)].push_back(name_to_ind.at(s));
  }
  
  std::vector<std::vector<std::pair<int,int>>> queries(n);
  
  for(int k = 0; k < q; k++) {
    std::string s; int b;
    std::cin >> s; std::cin >> b;
    int idx = name_to_ind.at(s);
    queries[idx].push_back({k, b});
  }
  
  
  solve_for(root, children, queries);
  
  for(int k = 0; k < q; k++) {
    std::cout << ind_to_name[solution[k]] << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::size_t t;
  for (std::cin >> t; t > 0; --t) testcase();
  return 0;
}
