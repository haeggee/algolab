#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

int max_num_fam(std::vector<int> &comp_of_size, int k) {
    // vector is size == k+1
    int num = comp_of_size[k];
    if(k == 4) {
        // match 3 with ones, then take pairs of 2, match rest
        int match_three_one = std::min(comp_of_size[3], comp_of_size[1]);
        int remaining3 = comp_of_size[3] - match_three_one;
        int remaining1 = comp_of_size[1] - match_three_one;
        // add remaining size 3 to 2
        int remaining2 = comp_of_size[2] + remaining3;
        // if num2 is not divisible by two, we can possibly combine
        // the one leftover with the single
        if(remaining2 % 2 == 1) remaining1 += 2;
        num += match_three_one + remaining2 / 2 + remaining1 / 4;
        
    } else if(k == 3) {
        // match 2 with ones, add rest
        int match_two_one = std::min(comp_of_size[2], comp_of_size[1]);
        int remaining2 = comp_of_size[2] - match_two_one;
        int remaining1 = comp_of_size[1] - match_two_one;
        // the remaining 2size comp have to be div by 2 (two together is one family)
        num += match_two_one + remaining2 / 2 + remaining1 / 3;
    } else if(k == 2) {
        // just take the single comp and divide by 2
        num += comp_of_size[1] / 2;
    }
    return num;
}


void testcase() {
    Index n, k, f0;
    double s0;
    std::cin >> n >> k >> f0 >> s0;

    typedef std::pair<K::Point_2,Index> IPoint;
    std::vector<IPoint> points;
    points.reserve(n);
    for (Index i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points.emplace_back(K::Point_2(x, y), i);
    }
    Delaunay t;
    t.insert(points.begin(), points.end());
    EdgeV edges;
    edges.reserve(3*n); // there can be no more in a planar graph
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        Index i1 = e->first->vertex((e->second+1)%3)->info();
        Index i2 = e->first->vertex((e->second+2)%3)->info();
        // ensure smaller index comes first
        if (i1 > i2) std::swap(i1, i2);
        edges.emplace_back(i1, i2, t.segment(e).squared_length());
    }
    std::sort(edges.begin(), edges.end(),
            [](const Edge& e1, const Edge& e2) -> bool {
            return std::get<2>(e1) < std::get<2>(e2);
                });


    // for testcases 1-2: just look at smallest distance, bc otherwise not enough tents
    // std::cout << long(std::get<2>(edges[0])) << " ";


    boost::disjoint_sets_with_storage<> uf(n);
    std::vector<Index> num_tents(n, 1);
    Index n_components = n;
    std::vector<int> comp_of_size(k + 1, 0);
    comp_of_size[1] = n;
    double last_dist = 0;
    for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
        // determine components of endpoints
        Index c1 = uf.find_set(std::get<0>(*e));
        Index c2 = uf.find_set(std::get<1>(*e));
        last_dist = std::get<2>(*e);
        if (c1 != c2) {
            Index n1 = num_tents[c1];
            Index n2 = num_tents[c2];
            uf.link(c1, c2);
            Index c3 = uf.find_set(std::get<1>(*e));
            // set unused indices to zero
            num_tents[c1] = num_tents[c2] = 0;
            // cap it at k
            num_tents[c3] = std::min(n1 + n2, k);
            comp_of_size[n1]--; comp_of_size[n2]--;
            comp_of_size[num_tents[c3]]++;
            if (max_num_fam(comp_of_size, k) < f0) break;
        }
    }
    
    std::cout << long(last_dist) << " ";


    // repeat process with adding edges < s0, then find max num families
    boost::disjoint_sets_with_storage<> uf_s0(n);
    num_tents = std::vector<Index>(n, 1);
    comp_of_size = std::vector<int>(k + 1, 0);
    comp_of_size[1] = n;

    n_components = n;
    for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
        // determine components of endpoints
        Index c1 = uf_s0.find_set(std::get<0>(*e));
        Index c2 = uf_s0.find_set(std::get<1>(*e));
        double dist = std::get<2>(*e);
        if(dist >= s0) {
            break;
        }
        if (c1 != c2) {
            Index n1 = num_tents[c1];
            Index n2 = num_tents[c2];
            uf_s0.link(c1, c2);
            Index c3 = uf_s0.find_set(std::get<1>(*e));
            // set unused indices to zero
            num_tents[c1] = num_tents[c2] = 0;
            // cap component size at k
            num_tents[c3] = std::min(n1 + n2, k);
            comp_of_size[n1]--; comp_of_size[n2]--;
            comp_of_size[num_tents[c3]]++;
            if (--n_components == 1) break;
        }
    }
    std::cout << max_num_fam(comp_of_size, k) << std::endl;
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
