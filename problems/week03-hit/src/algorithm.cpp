#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
using namespace std;

int main()
{
  std::ios_base::sync_with_stdio(false);
  int n; std::cin >> n;
  while(n > 0) {
    long x, y, a, b;
    cin >> x; cin >> y; cin >> a; cin >> b;
    R ray(P(x,y), P(a,b));
    bool hits = false;
    for(int i = 0; i < n; i++) {
      long r, s, t, u;
      cin >> r; cin >> s; cin >> t; cin >> u;
      if(!hits) {
        S seg(P(r,s), P(t,u));
        hits = CGAL::do_intersect(ray,seg) ? true : hits;
      }
    }
    string res = hits ? "yes" : "no";
    cout << res << endl;
    cin >> n;
  }
}
