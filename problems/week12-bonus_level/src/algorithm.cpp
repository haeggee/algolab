#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
// Includes
// ========
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};


int ind(int i, int j, int n) {
    return  i * n + j;
}

void testcase() {
    int n; std::cin >> n;
    int nn = n * n;
    int sum_a = 0;
    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            std::cin >> a[i][j];
            sum_a += a[i][j];
        }
    }

    graph G(2 * nn);
    edge_adder adder(G);
    int max_a = 100;
    const int v_source = nn;
    const int v_sink = nn - 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i < n - 1) adder.add_edge(nn + ind(i,j,n), ind(i+1,j,n), 1, 0);
            if(j < n - 1) adder.add_edge(nn + ind(i,j,n), ind(i,j+1,n), 1, 0);
            if(!( (i == 0 && j == 0) || (i == n - 1 && j == n - 1))) {
                adder.add_edge(ind(i,j,n), nn + ind(i,j,n), 1, -a[i][j] + max_a);
            }
        }
    }
    
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
    int cost1 = boost::find_flow_cost(G);
    // std::cerr << cost1 << " " << (4 * n - 6) * max_a << std::endl;
    std::cout << (4 * n - 6) * max_a - cost1 + a[0][0] + a[n-1][n-1] << std::endl;
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
