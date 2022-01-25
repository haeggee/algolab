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


void testcase() {

    int c, g, b, k, a; 
    std::cin >> c >> g >> b >> k >> a;
    // Create graph, edge adder class and propery maps
    graph G(c + g);
    edge_adder adder(G);  
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);

    const int v_source = boost::add_vertex(G);

    int sum_elephants = 0;
    for(int i = 0; i < g; i++) {
        int x, y, d, e;
        std::cin >> x >> y >> d >> e;
        sum_elephants += e;
        adder.add_edge(x, c + i, e, d);
        adder.add_edge(c + i, y, e, 0);
    }
    
    // source
    adder.add_edge(v_source, k, sum_elephants, 0);

    int l = 0;
    int s_flow = 0;
    out_edge_it e, eend;
    boost::successive_shortest_path_nonnegative_weights(G, v_source, a);
    int cost = boost::find_flow_cost(G);
    
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
        s_flow += c_map[*e] - rc_map[*e];     
    }

    // this is a simple heuristic: we save the binary search
    // if cost is not the bottleneck anyway
    if(cost <= b) { 
        std::cout << s_flow << std::endl;
        return;
    }

    int r = s_flow;
    while(l <= r) {
        int mid = (l + r) / 2;
        // change capacity
        const edge_desc e_s = boost::edge(v_source, k, G).first;
        const edge_desc rev_e = r_map[e_s];
        c_map[e_s] = mid;
        c_map[rev_e] = 0; // reverse edge has no capacity!
        boost::successive_shortest_path_nonnegative_weights(G, v_source, a);
        int cost = boost::find_flow_cost(G);
        out_edge_it e, eend;
        if(cost <= b) { // cost is okay, i.e. go higher
            l = mid + 1;
        } else {
            r = mid;
            if(l == r) break;
        }
    }
    std::cout << l - 1 << std::endl;
}
int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
