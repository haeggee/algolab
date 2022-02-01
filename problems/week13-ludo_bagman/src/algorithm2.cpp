// ALGOLAB BGL Tutorial 3
// Code demonstrating 
// - MinCostMaxFlow with arbitrary edge costs using cycle_canceling
// - MinCostMaxFlow with non-negative edge costs using successive_shortest_path_nonnegative_weights

// Includes
// ========
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <tuple>

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
    //std::cout << "from: " << from << " to: " << to << " capacity " << capacity << " cost: " << cost << std::endl;
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


void testcase() {
    int e, w, m, d, p, l; std::cin >> e >> w >> m >> d >> p >> l;
    std::vector<std::tuple<int, int, int>> good_e_w(m);
    std::vector<std::tuple<int, int, int>> bad_e_w(d);
    for(int i = 0; i < m; i++) {
        int u, v, r; std::cin >> u >> v >> r;
        good_e_w[i] = std::make_tuple(u, v, r);
    }
    for(int i = 0; i < d; i++) {
        int u, v, r; std::cin >> u >> v >> r;
        bad_e_w[i] = std::make_tuple(u, v, r);
    }
    // if( p < e * l || p < w*l) {
    //     std::cout << "No schedule!" << std::endl;
    //     return;
    // }
    int n = e + w + e + w + 3 + 2;
    graph G(n);
    edge_adder adder(G);
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);

    int offset_bad = e+w;
    int offset_pre = e+w+offset_bad;
    int offset_right_good = offset_pre+1;
    int offset_right_bad = offset_pre+2;
    int start = n - 2;
    int end = n-1;
    for(int i = 0; i < m; i++) {
        adder.add_edge(std::get<0>(good_e_w[i]), std::get<1>(good_e_w[i])+e, 1L, std::get<2>(good_e_w[i]));
    }
    for(int i = 0; i < d; i++) {
        adder.add_edge(offset_bad + std::get<0>(bad_e_w[i]), offset_bad + std::get<1>(bad_e_w[i])+e, 1L, std::get<2>(bad_e_w[i]));
    }
    for(int i = 0; i < e; i++) {
        adder.add_edge(offset_pre, i, p+1, 0);
        adder.add_edge(offset_pre, offset_bad+i, p+1, 0);
    }
    for(int i = 0; i < e; i++) {
        adder.add_edge(start, i, l, 0);
    }
    adder.add_edge(start, offset_pre, p-(e*l), 0);

    for(int i = 0; i < w; i++) {
        adder.add_edge(i+e, offset_right_good, l, 0);
        adder.add_edge(i+e, offset_right_bad, p+1, 0);
    }

    for(int i = 0; i < w; i++) {
        adder.add_edge(i+offset_bad+e, offset_right_bad, p+1, 0);
    }
    adder.add_edge(offset_right_good, end, w*l, 0);
    adder.add_edge(offset_right_bad, end, p-w*l, 0);

    boost::successive_shortest_path_nonnegative_weights(G, start, end);
    int cost2 = boost::find_flow_cost(G);

    int s_flow = 0;
    out_edge_it ee, eend;
    for(boost::tie(ee, eend) = boost::out_edges(boost::vertex(start,G), G); ee != eend; ++ee) {
        s_flow += c_map[*ee] - rc_map[*ee];
    }

    if(s_flow == p) {
        std::cout << cost2 << std::endl;
    } else {
        std::cout << "No schedule!" << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t; std::cin >> t;

    for(int i = 0; i < t; i++) testcase();

    return 0;
}