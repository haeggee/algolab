/* Tags: Delaunay Triangulation, Union-Find, Connected Components, Closest Neighbor 

  Key idea: 1:1 correspondence between points being connected (connected components in EMST)
                <==>
                we can move between the disks of the points
                (for a radius >= 2 * minimal distance betw. them) 
            Can copy code from the EMST template, and adapt:
            * three UF structures, one for the given radius U_p,
              U_a: minimum power needed to execute _all_ missions
              U_b: minimum power needed to execute same set of missions as with inital p
            * First connect components of U_p with edges <= p
            * then see, for each mission, if 4*distance <= p and
              components are connected, mission can be executed
            * If can be executed: enlarge U_b until it is covered
            * In any case: enlarge U_a until it is covered

*/
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;

// As edges are not explicitly represented in the triangulation, we extract them
// from the triangulation to be able to sort and process them. We store the
// indices of the two endpoints, first the smaller, second the larger, and third
// the squared length of the edge. The i-th entry, for i=0,... of a tuple t can
// be accessed using std::get<i>(t).
typedef std::tuple<Index,Index,double> Edge;
typedef std::vector<Edge> EdgeV;

void solve() {
  Index n, m;
  double p;
  std::cin >> n >> m >> p;

  // read points
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> jammers;
  jammers.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    jammers.push_back({K::Point_2(x, y), i});
  }
  // construct triangulation
  Triangulation t;
  t.insert(jammers.begin(), jammers.end());
  
  // extract edges and sort by (squared) length
  // This step takes O(n log n) time (for the sorting).
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

  // setup and initialize union-find data structure for initial power
  boost::disjoint_sets_with_storage<> uf_p(n);
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    // determine components of endpoints
    Index c1 = uf_p.find_set(std::get<0>(*e));
    Index c2 = uf_p.find_set(std::get<1>(*e));
    double squared_dist = std::get<2>(*e);
    if (squared_dist <= p){
      if(c1 != c2) {
       // this edge connects two different components => part of the emst
        uf_p.link(c1, c2);
      }
    } else {
      break;
    }
  }


  K::FT a = 0, b = 0;
  // setup and initialize union-find data structure for 
  // a: minimum power needed to execute _all_ missions
  // b: minimum power needed to execute same set of missions as with inital p

  boost::disjoint_sets_with_storage<> uf_a(n);
  boost::disjoint_sets_with_storage<> uf_b(n);

  // we continously enlarge the tree components for a and b,
  // so we need to remember where we left off for new missions
  EdgeV::const_iterator e_iter_a = edges.begin();
  EdgeV::const_iterator e_iter_b = edges.begin();
  Index n_components_a = n;
  Index n_components_b = n;
  for (Index j = 0; j < m; j++) {
    int x0, y0, x1, y1; std::cin >> x0 >> y0 >> x1 >> y1;
    auto sj = K::Point_2(x0, y0);
    auto tj = K::Point_2(x1, y1);

    auto vertex_sj = t.nearest_vertex(sj);
    auto vertex_tj = t.nearest_vertex(tj);
    double dist_sj = CGAL::squared_distance(sj, vertex_sj->point());
    double dist_tj = CGAL::squared_distance(tj, vertex_tj->point());
    K::FT max_dist_start = 4 * std::max(dist_sj, dist_tj);

    Index vi0 = vertex_sj->info();
    Index vi1 = vertex_tj->info();

    // mission is possible with intial power
    if(max_dist_start <= p && uf_p.find_set(vi0) == uf_p.find_set(vi1)) {
      std::cout << "y";
      double squared_dist_needed = 0;
      // since covered, increase the tree of b until points are connected
      while(uf_b.find_set(vi0) != uf_b.find_set(vi1) && e_iter_b != edges.end()
            && n_components_b != 0) {
        Index c1 = uf_b.find_set(std::get<0>(*e_iter_b));
        Index c2 = uf_b.find_set(std::get<1>(*e_iter_b));
        squared_dist_needed = std::get<2>(*e_iter_b);
        if(c1 != c2) {
          // this edge connects two different components
          uf_b.link(c1, c2);
          n_components_b--;
        }
        e_iter_b++;
      }
      b = std::max({squared_dist_needed, max_dist_start, b});
    } else {
      std::cout << "n";
    }

    // same as above but for trees a
    double squared_dist_needed = 0;
    // since covered, increase the tree of b until points are connected
    while(uf_a.find_set(vi0) != uf_a.find_set(vi1) && e_iter_a != edges.end()
           && n_components_a != 0) {
      Index c1 = uf_a.find_set(std::get<0>(*e_iter_a));
      Index c2 = uf_a.find_set(std::get<1>(*e_iter_a));
      squared_dist_needed = std::get<2>(*e_iter_a);
      if(c1 != c2) {
        // this edge connects two different components
        uf_a.link(c1, c2);
        n_components_a--;
      }
      e_iter_a++;
    }
    a = std::max({squared_dist_needed, max_dist_start, a});
  }

  std::cout << "\n" << a << "\n" << b << "\n";
}

int main() 
{
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  std::size_t t;
  for (std::cin >> t; t > 0; --t) solve();
  return 0;
}