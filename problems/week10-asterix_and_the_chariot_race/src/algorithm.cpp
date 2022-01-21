
/* Tags: DFS, Tree, Recursion
    IDEA:
      do dfs starting from root node 0 (as we have a tree)
      and recursively solve - we always have 3 cases, as explained below
    return 3 optimal values:
    - 0: opt cost if this node is definitely taken
    - 1: opt cost if this node is covered by parent, but might still be taken
    - 2: opt cost if this node is _not_ covered by parent, but might still be taken
    ---------------
    then for current node, we have: 
    selected opt    = cost[v] + sum_covered
    covered opt     = min(sum_not_covered, self_selected)
    not covered opt = min(sum_not_covered + best_diff, self_selected)
*/
#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
tuple<int,int,int> solve(vector<int> &costs, vector<vector<int>> &edges, int v) {
    if(edges[v].size() == 0) {
        return {costs[v], 0, costs[v]};
    }

    int cost_v = costs[v];
    int best_diff = numeric_limits<int>::max();
    int sum_covered = 0;
    int sum_not_covered = 0;
    for(int i : edges[v]) {
        // std::cerr << "cerr:" << i << "\n";
        auto rec = solve(costs, edges, i);
        sum_covered += get<1>(rec);
        sum_not_covered += get<2>(rec);
        int selected = get<0>(rec);
        best_diff = min(best_diff, selected - get<2>(rec));
    }

    // if we select this node, all children are covered 
    int self_selected = cost_v + sum_covered;
    
    // the other cases are as described above, but we
    // might still select the node __if__ it is cheaper

    // covered: add nothing to others not covered
    int self_covered = min(sum_not_covered, self_selected);

    // not covered: need to select one child, take the cheapest
    int self_not_covered = min(sum_not_covered + best_diff, self_selected);
    return {self_selected, self_covered, self_not_covered};
}

// Main
void testcase() {
  // build graph
  int n;
  std::cin >> n;
  
  vector<vector<int>> edges(n, vector<int>(0));
  
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    edges[u].push_back(v);
  }
  
  vector<int> costs(n);
  for(int i = 0; i < n; i++) {
    std::cin >> costs[i];
  }
  // best solution is the non covered case for the root, as it has no parent
  std::cout << get<2>(solve(costs, edges, 0)) << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
