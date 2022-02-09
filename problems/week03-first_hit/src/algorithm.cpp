//1
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
using namespace std;

double floor_to_double(const K::FT& x)
{
 double a = std::floor(CGAL::to_double(x));
 while (a > x) a -= 1;
 while (a+1 <= x) a += 1;
 return a;
}

int main()
{
  ios_base::sync_with_stdio(false);
  int n; std::cin >> n;
  while(n > 0) {
    long x, y, a, b;
    cin >> x; cin >> y; cin >> a; cin >> b;
    P source = P(x,y);
    P closest_hit;
    R ray(source, P(a,b));
    S hit_seg;
    bool hits = false;
    vector<S> segments(n);
    
    for(int i = 0; i < n; i++) {
      long r, s, t, u;
      cin >> r; cin >> s; cin >> t; cin >> u;
      P seg_p1 = P(r,s);
      P seg_p2 = P(t,u);
      S seg(seg_p1, seg_p2);
      segments[i] = seg;
    }
    random_shuffle(segments.begin(), segments.end());
    
    for(int i = 0; i < n; i++) {
      S seg = segments[i];
      P seg_p1 = seg.source();
      P seg_p2 = seg.target();
      if(!hits && CGAL::do_intersect(ray,seg)) { // no hit yet, i.e. only have ray
        auto o = CGAL::intersection(ray,seg);
        if (const P* op = boost::get<P>(&*o)) { // point intersec
          closest_hit = *op;
        } else { // segment intersec
          closest_hit = CGAL::has_larger_distance_to_point(source, seg_p1, seg_p2) ? seg_p2 : seg_p1;
        }
        hit_seg = S(source, closest_hit);
        hits = true;
      } else if(CGAL::do_intersect(hit_seg,seg)) { // hit once, so we have a segment
        auto o = CGAL::intersection(hit_seg,seg);
        if (const P* op = boost::get<P>(&*o)) { // point intersec
          closest_hit = *op;
          hit_seg = S(source, closest_hit);
        } else { // segment intersec
          closest_hit = CGAL::has_larger_distance_to_point(source, seg_p1, seg_p2) ? seg_p2 : seg_p1;
          hit_seg = S(source, closest_hit);
        }
      }
    }
    if(!hits) 
      cout << "no" << endl;
    else
      cout << long(floor_to_double(closest_hit.x())) << " " << long(floor_to_double(closest_hit.y())) << endl; 
    cin >> n;
  }
}
