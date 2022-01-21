/* Tags: Delaunay Triangulation, Union-Find, Connected Components, Closest Neighbor 

  Key idea: Close relation to Golden Eye problem:
            1:1 correspondence between points being connected (connected components in EMST)
                <==>
                we can move between the disks of the points
                (for a radius >= 2 * minimal distance betw. them) 
            Can copy code from the EMST template, and adapt:
            * two UF structures, one for given initial radius with s,
              one for radius needed to get k
            * for first problem (max bones):
              for each component of tree, store the number of bones reachable
              (i.e. 4 *distance to closest point <= s)
              This can be done via a simple array, as UF comp. have index <= n
              Upon merging, add together the numbers. At the end (when all edges <= s considerd)
              look for max
            * for second problem (min. radius b to get k):
              Have additional edges from each bone to closest point with edge weight 4 * dist.
              Sort as usual, then do same procedure as above (i.e. UF) until one comp has >= k bones
              Then the latest edge considered has minimal radius needed

              Why 4 * dist? ->
              for correct b, need to consider radius over all edges, but for edges between trees
              we have that dist = radius / 2. When we sort, we would thus mix up scale
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
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

// As edges are not explicitly represented in the triangulation, we extract them
// from the triangulation to be able to sort and process them. We store the
// indices of the two endpoints, first the smaller, second the larger, and third
// the squared length of the edge. The i-th entry, for i=0,... of a tuple t can
// be accessed using std::get<i>(t).
typedef std::tuple<Index,Index,double> Edge;
typedef std::vector<Edge> EdgeV;

std::ostream& operator<<(std::ostream& o, const Edge& e) {
  return o << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e);
}

void testcase() {
  Index n, m, k;
  long s;
  std::cin >> n >> m >> s >> k;

  // read points: first, we read all points and store them into a vector,
  // together with their indices
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> oak_trees;
  oak_trees.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    oak_trees.emplace_back(K::Point_2(x, y), i);
  }
  Delaunay t;
  t.insert(oak_trees.begin(), oak_trees.end());

  // store the number of bones that are in reach for each oak tree
  std::vector<Index> bones_per_comp(n, 0);
  std::vector<IPoint> points;
  points.reserve(m);
  EdgeV edges_ext;
  edges_ext.reserve(m); // there can be no more in a planar graph

  for (Index i = 0; i < m; ++i) {
    int x, y;
    std::cin >> x >> y;
    auto p = K::Point_2(x, y);
    auto v = t.nearest_vertex(p);
    double dist = CGAL::squared_distance(p, v->point());
    if(4 * K::FT(dist) <= s) {
      bones_per_comp[v->info()] += 1;
    }
    points.emplace_back(p, i);
    edges_ext.emplace_back(v->info(), n + i, 4 * dist);
  }

  // extract edges and sort by (squared) length
  // This step takes O(n log n) time (for the sorting).
  EdgeV edges;
  edges.reserve(3*n + m); // there can be no more in a planar graph

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

  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  // ... and process edges in order of increasing length
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    // determine components of endpoints
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    double squared_dist = std::get<2>(*e);
    if(squared_dist <= s) {
        if (c1 != c2) {
            // this edge connects two different components => merge number of bones
            auto b1 = bones_per_comp[c1];
            auto b2 = bones_per_comp[c2];
            bones_per_comp[c1] = 0;
            bones_per_comp[c2] = 0;
            uf.link(c1, c2);
            Index c3 = uf.find_set(std::get<0>(*e));
            bones_per_comp[c3] = b1 + b2;
            if (--n_components == 1) break;
        }
    } else break;
  }

  std::cout << *std::max_element(bones_per_comp.begin(), bones_per_comp.end()) << " ";
  
  // find minimal readius for k bones
  // by considering edges to bones as well
  // -- for code simplicity, redo whole union-find procedure
  std::vector<Index> bones(n + m, 0);
  for (Index i = 0; i < m; ++i) {
    edges.push_back(edges_ext[i]);
    bones[n + i] = 1;
  }
  std::sort(edges.begin(), edges.end(),
        [](const Edge& e1, const Edge& e2) -> bool {
          return std::get<2>(e1) < std::get<2>(e2);
            });

  boost::disjoint_sets_with_storage<> uf_ext(n + m);
  K::FT b_squared = 0;
  // ... and process edges in order of increasing length
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    // determine components of endpoints
    Index i1 = std::get<0>(*e);
    Index i2 = std::get<1>(*e);
    Index c1 = uf_ext.find_set(i1);
    Index c2 = uf_ext.find_set(i2);
    double squared_dist = std::get<2>(*e);
    if (c1 != c2) {
        // this edge connects two different components => merge number of bones
        auto b1 = bones[c1];
        auto b2 = bones[c2];
        bones[c1] = 0;
        bones[c2] = 0;
        uf_ext.link(c1, c2);
        Index c3 = uf_ext.find_set(std::get<0>(*e));
        bones[c3] = b1 + b2;
        if (b1 + b2 >= k) {
          b_squared = squared_dist;
          break;
        }
    }
  }
  std::cout << b_squared << "\n";
}

int main() 
{
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  std::size_t t;
  for (std::cin >> t; t > 0; --t) testcase();
  return 0;
}
