#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
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

struct edge {
    int u;
    int v;
    int r;
};

void testcase() {
    int e, w, m, d, p, l;
    std::cin >> e >> w >> m >> d >> p >> l;
    std::vector<edge> nondiff(m);
    for(int i = 0; i < m; i++) {
        int u, v, r;
        std::cin >> u >> v >> r;
        nondiff[i] = {u, v, r};
    }
    std::vector<edge> diff(d);
    for(int i = 0; i < d; i++) {
        int u, v, r;
        std::cin >> u >> v >> r;
        diff[i] = {u, v, r};
    }
    int min_needed = std::max(e * l, w * l);
    if(min_needed > p) {
        std::cout << "No schedule!" << std::endl;
        return;
    }
    graph G(2 * (e + w));
    edge_adder adder(G);
    // Retrieve the capacity map and reverse capacity map
    auto c_map = boost::get(boost::edge_capacity, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    // edge from sink to two paths: one for the l matches for each, one for the rest
    // same goes for sink 
    // --> by forcing the "rest" path to have at max p-e*l matches, we have at least l matches
    // for each 
    int source = boost::add_vertex(G);
    int source_out_l = boost::add_vertex(G);
    int source_out_rest = boost::add_vertex(G);
    int sink = boost::add_vertex(G);
    int sink_out_l = boost::add_vertex(G);
    int sink_out_rest = boost::add_vertex(G);
    
    for(int i = 0; i < e; i++) {
        adder.add_edge(source_out_l, i, l, 0);
        adder.add_edge(source_out_rest, i, std::numeric_limits<long>::max(), 0);
        adder.add_edge(source_out_rest, e + w + i, std::numeric_limits<long>::max(), 0);
    }

    for(int i = 0; i < w; i++) {
        adder.add_edge(2 * e + w + i, sink_out_rest, std::numeric_limits<long>::max(), 0);
        adder.add_edge(e + i, sink_out_rest, std::numeric_limits<long>::max(), 0);
        adder.add_edge(e + i, sink_out_l, l, 0);
    }
    
    for(auto ed : nondiff) {  
        adder.add_edge(ed.u, e + ed.v, 1, ed.r);
    }
    // diff matches are in a copy of e + w, where the e and w edges are connected to
    // the "rest" source and sink nodes with capacity
    for(auto ed : diff) {
        adder.add_edge(e + w + ed.u, 2 * e + w + ed.v, 1, ed.r);
    }
    adder.add_edge(source, source_out_l, e * l, 0);
    adder.add_edge(source, source_out_rest, p - e * l, 0);
    adder.add_edge(sink_out_l, sink, w * l, 0);
    adder.add_edge(sink_out_rest, sink, p - w * l, 0);

    boost::successive_shortest_path_nonnegative_weights(G, source, sink);
    int risk = boost::find_flow_cost(G);
    
    int flow = c_map[boost::edge(source, source_out_l, G).first] - rc_map[boost::edge(source, source_out_l, G).first];
    flow += c_map[boost::edge(source, source_out_rest, G).first] - rc_map[boost::edge(source, source_out_rest, G).first];
    if(flow != p) {
        std::cout << "No schedule!" << std::endl;
        return;
    } else {
        std::cout << risk << std::endl;
    }

    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
