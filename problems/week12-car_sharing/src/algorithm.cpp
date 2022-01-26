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


struct Request {
    int si;
    int ti;
    int di;
    int ai;
    int pi;
};

void testcase() {
    long n, s;
    std::cin >> n >> s;
    std::vector<int> l(s);
    long total_cars = 0;
    for(int i = 0; i < s; i++) {
        std::cin >> l[i];
        total_cars += l[i];
    }
    
    std::vector<std::set<int>> timestamps_per_s(s);
    
    std::vector<Request> requests(n);
    long max_arrival = 100'000;
    long max_p = 100;
    for(int i = 0; i < n; i++) {
        int si, ti, di, ai, pi;
        std::cin >> si >> ti >> di >> ai >> pi;
        requests[i] = {si - 1, ti - 1, di, ai, pi};
        if(di != 0) timestamps_per_s[si - 1].insert(di);
        if(ai != max_arrival) timestamps_per_s[ti - 1].insert(ai);
        // std::cerr << s * di / 30 + si - 1 << " " << s * ai / 30 + ti - 1 <<  " " << pi << std::endl;
    }

    int sum_dist_nodes = 0;
    std::vector<std::unordered_map<int, int>> map_to_g(s); // map (si, ti) -> j in graph
    for(int i = 0; i < s; i++) {
        map_to_g[i].insert({0, sum_dist_nodes++});
        map_to_g[i].insert({max_arrival, sum_dist_nodes++});
        for(auto t : timestamps_per_s[i]) {
            map_to_g[i].insert({t, sum_dist_nodes++});
            // std::cerr << "i " << i << " " << t  << "\n";
        }
    }
    graph G(sum_dist_nodes);
    const int v_source = boost::add_vertex(G);
    const int v_sink = boost::add_vertex(G);
    edge_adder adder(G);
    
    for(auto r : requests) {
        int si, ti, di, ai, pi;
        si = r.si; ti = r.ti; di = r.di;
        ai = r.ai; pi = r.pi;
        // std::cerr << -pi + max_p * (ai - di) << std::endl;
        adder.add_edge(map_to_g[si].at(di) , map_to_g[ti].at(ai), 1, -pi + max_p * (ai - di));
    }

    for(int i = 0; i < s; i++) {
        // source to time 0
        adder.add_edge(v_source, map_to_g[i].at(0), l[i], 0);
        adder.add_edge(map_to_g[i].at(max_arrival), v_sink, total_cars, 0);
        // time 0 to first time
        if(timestamps_per_s[i].size() > 0) {
            long min_ti = *timestamps_per_s[i].begin();
            adder.add_edge(map_to_g[i].at(0), map_to_g[i].at(min_ti), total_cars, min_ti * max_p);
            // second to last to max time
            long max_ti = *timestamps_per_s[i].rbegin();
            adder.add_edge(map_to_g[i].at(max_ti), map_to_g[i].at(max_arrival), total_cars, (max_arrival - max_ti) * max_p);
            auto t2 = timestamps_per_s[i].begin();
            auto t1 = t2++;
            for(; t2 != timestamps_per_s[i].end(); t1++, t2++) {
                adder.add_edge(map_to_g[i].at(*t1), map_to_g[i].at(*t2), total_cars, (*t2 - *t1) * max_p);
            }
        } else {
            adder.add_edge(map_to_g[i].at(0), map_to_g[i].at(max_arrival), total_cars, (max_arrival) * max_p);
        }
        
    }

    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
    long cost = boost::find_flow_cost(G);
    // std::cout << -(cost) << "\n";
    std::cout << -(cost - (total_cars * max_p * max_arrival)) << "\n";

//   // // Retrieve the capacity map and reverse capacity map
//   const auto c_map = boost::get(boost::edge_capacity, G);
//   const auto rc_map = boost::get(boost::edge_residual_capacity, G);

//   // Iterate over all the edges to print the flow along them
//   auto edge_iters = boost::edges(G);
//   std::cerr << v_source << " " << v_sink;
//   for (auto edge_it = edge_iters.first; edge_it != edge_iters.second; ++edge_it) {
//     const edge_desc edge = *edge_it;
//     const long flow_through_edge = c_map[edge] - rc_map[edge];
//     std::cerr << "edge from " << boost::source(edge, G) << " to " << boost::target(edge, G)
//               << " with capacity " << c_map[edge] 
//               << " runs " << flow_through_edge
//               << " units of flow (negative for reverse direction). \n";
//   }
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
