

#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

// CGAL
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
// face handle with index to identify faces
typedef CGAL::Triangulation_face_base_with_info_2<size_t,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

void testcase(size_t n) {
    std::vector<K::Point_2> pts;
    pts.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        pts.push_back(K::Point_2(x, y));
    }
    // construct triangulation
    Triangulation t;
    t.insert(pts.begin(), pts.end());
    

    // name all 
    size_t num_faces = 1; 
    for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f)
        f->info() = num_faces++;
    

    // adjacency list
    std::vector<std::vector<std::pair<size_t,double>>> edges(num_faces); 
    for (auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f) {
        int u = f->info();
        
        for (int i = 0; i < 3; ++i) {
            auto f2 = f->neighbor(i);
            int v = t.is_infinite(f2) ? 0 : f2->info();
            auto p1 = f->vertex((i + 1) % 3)->point();
            auto p2 = f->vertex((i + 2) % 3)->point();
            // inputs are < 2^24, so double suffices
            double dist = CGAL::squared_distance(p1, p2);
            edges[u].push_back({v, dist});
            if (v == 0) { // we do not loop over infinite faces, so add here
                edges[v].push_back({u, dist});
            }
        }
    }

    std::vector<double> bottleneck(num_faces, -1);

    // get the maximal minimal bottleneck for each face, using a priority queue
    // --> priority queue per default gives the largest element
    // IMPORTANT to use distance as first argument here, bc it;s the first ordered
    std::priority_queue<std::pair<double, size_t>> Q;
    Q.push({std::numeric_limits<double>::max(), 0}); // infinite face has unlimited bottleneck
        
    while(!Q.empty()) {
        auto p = Q.top(); Q.pop();
        double val = p.first;
        size_t u = p.second;
        // IMPORTANT to see here that the value will never improve, i.e. visited are done
        // --> starting from the infinite face, all others are bottlenecked by
        // the convex hull edges, and then the direct neighbors.
        // Since we extract the maximum
        if(bottleneck[u] != -1) {
            continue;
        } 
        bottleneck[u] = val;

        for(auto neighb : edges[u]) {
            double dist = neighb.second;
            size_t v = neighb.first;
            // unvisited, choose min -> works bc priority queue is for max
            if(bottleneck[v] == -1) Q.push({std::min(dist, val), v});
        }
    }

    // answer queries
    size_t m;
    std::cin >> m;
    for(size_t j = 0; j < m; j++) {
        int x, y;
        double d;
        std::cin >> x >> y >> d;
        auto p = K::Point_2(x,y);
        double dist = CGAL::squared_distance(p, t.nearest_vertex(p)->point());
        // std::cerr << d << " " << dist << std::endl;
        if(d > dist) {
            // too close, not possible
            std::cout << "n";
            continue; 
        }

        auto f = t.locate(p);
        auto i = t.is_infinite(f) ? 0 : f->info();
        // bottleneck is too small ?
        4 * d > bottleneck[i] ? std::cout << "n" : std::cout << "y";
    }
    std::cout << std::endl;
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;
    while(n != 0) {
        testcase(n);
        std::cin >> n;
    }
}
