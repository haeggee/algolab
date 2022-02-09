#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef K::Point_2 P;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

using namespace std;

double ceil_to_double(const K::FT& x)
{
 double a = std::ceil((CGAL::to_double(x)));
 while (a-1 >= x) a -= 1;
 while (a < x) a += 1;
 return a;
}

int main()
{
  ios_base::sync_with_stdio(false);
  int n; std::cin >> n;
  while(n > 0) {
    vector<P> points(n);
    for(int i = 0; i < n; i++) {
      long x, y;
      cin >> x; cin >> y;
      P p = P(x,y);
      points[i] = p;
    }
    // random_shuffle(points.begin(), points.end());
    Min_circle mc(points.begin(), points.end(), true);
    Traits::Circle c = mc.circle();
    cout << long(ceil_to_double(CGAL::sqrt(c.squared_radius()))) << endl; 
    cin >> n;
  }
}
