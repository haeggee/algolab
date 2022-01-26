// Includes
// ========
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, long> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;


// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> flow_graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;


// Custom edge adder class
class edge_adder {
 weighted_graph &G;

 public:
  explicit edge_adder(weighted_graph &G) : G(G) {}
  void add_edge(int from, int to, long weight) {
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    w_map[e] = weight;   // new assign cost
  }
};


// Custom edge adder class, highly recommended
class edge_adder_flow {
  flow_graph &G;

 public:
  explicit edge_adder_flow(flow_graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};


void testcase() {
    int n, m, a, s, c, d;
    std::cin >> n >> m >> a >> s >> c >> d;
    weighted_graph G(n);
    edge_adder adder(G);

    for(int i = 0; i < m; i++) {
        char w; int x, y, z;
        std::cin >> w >> x >> y >> z;
        adder.add_edge(x, y, z);
        if(w == 'L') {
            adder.add_edge(y, x, z);
        }
    }

    std::vector<int> agent(a);
    for(int i = 0; i < a; i++) {
        std::cin >> agent[i];
    }

    std::vector<int> shelter(s);
    for(int i = 0; i < s; i++) {
        std::cin >> shelter[i];
    }


    std::vector<std::vector<long>> distance_to(a, std::vector<long>(s));
    long max_dist = 0;
    for(int i = 0; i < a; i++) {
        std::vector<int> dist_map(n);
        boost::dijkstra_shortest_paths(G, agent[i],
            boost::distance_map(boost::make_iterator_property_map(
            dist_map.begin(), boost::get(boost::vertex_index, G))));
        for(int j = 0; j < s; j++) {
            distance_to[i][j] = dist_map[shelter[j]];
            if(distance_to[i][j] < std::numeric_limits<int>::max()) {
                max_dist = std::max(max_dist, distance_to[i][j]);
            }
        }
    }

    int l = 0, r = max_dist + c * d;

    while(l < r) {
        // compute matching for all edges dist + c * d <= mid
        flow_graph G_f(a + c * s);
        edge_adder_flow adder_f(G_f);
        int mid = (l + r) / 2;
        const int v_source = boost::add_vertex(G_f);
        const int v_sink = boost::add_vertex(G_f);
        for(int i = 0; i < a; i++) {
            adder_f.add_edge(v_source, i, 1);
            for(int j = 0; j < s; j++) {
                if(distance_to[i][j] + d <= mid) adder_f.add_edge(i, a + j, 1);
                if(c == 2) {
                    if(distance_to[i][j] + 2 * d <= mid) adder_f.add_edge(i, a + s + j, 1);
                }
            }
        }
        for(int j = 0; j < s; j++) {
            adder_f.add_edge(a + j, v_sink, 1);
            if(c == 2) adder_f.add_edge(a + s + j, v_sink, 1);
        }
        long flow = boost::push_relabel_max_flow(G_f, v_source, v_sink);
        if(flow == a) { // matching maximal -> all agents arrive at shelter
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    std::cout << l << std::endl;
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
