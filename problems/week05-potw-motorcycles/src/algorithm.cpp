///
#include <CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef std::tuple<long, long, long, int> T4;
typedef CGAL::Gmpq slope;
using namespace std;


struct T4_y0_descending {
  bool operator() (const T4& t0, const T4& t1) {
    return get<0>(t0) > get<0>(t1);
  }
};


void testcase()
{
  int n; std::cin >> n;
  vector<bool> rides_forever(n, true);
  vector<T4> indices(n);
  for(int i = 0; i < n; ++i) {
    long y0, x1, y1; cin >> y0; cin >> x1; cin >> y1;
    indices[i] = T4(y0, x1, y1, i);
  }
  
  std::sort(indices.begin(), indices.end(), T4_y0_descending());
  
  T4 curr_line = indices[0];
  slope y0 = (slope) get<0>(curr_line);
  slope x1 = (slope) get<1>(curr_line);
  slope y1 = (slope) get<2>(curr_line);
  slope min_abs_slope = (y1 - y0) / x1;
  
  for(int i = 1; i < n; i++) { // mark slopes going up in downpass
    curr_line = indices[i];
    y0 = (slope) get<0>(curr_line);
    x1 = (slope) get<1>(curr_line);
    y1 = (slope) get<2>(curr_line);
    int j = get<3>(curr_line);
    slope curr_slope = (y1 - y0) / x1;
    if(CGAL::abs(curr_slope) <= CGAL::abs(min_abs_slope))
      min_abs_slope = curr_slope; 
    else if(curr_slope > min_abs_slope)
      rides_forever[j] = false;
  }
  
  // curr_line = indices[n - 1];
  min_abs_slope = (y1 - y0) / x1;
  
  for(int i = n - 2; i >= 0; i--) { // mark slopes going down in uppass
    curr_line = indices[i];
    y0 = (slope) get<0>(curr_line);
    x1 = (slope) get<1>(curr_line);
    y1 = (slope) get<2>(curr_line);
    int j = get<3>(curr_line);
    slope curr_slope = (y1 - y0) / x1;
    if(CGAL::abs(curr_slope) < CGAL::abs(min_abs_slope)
        || (CGAL::abs(curr_slope) == CGAL::abs(min_abs_slope) 
            && curr_slope > min_abs_slope))
      min_abs_slope = curr_slope; 
    else if(curr_slope < min_abs_slope)
      rides_forever[j] = false;
  }
  
  
  for(int i = 0; i < n; i++ ) {
    if(rides_forever[i]) cout << i << " ";
  }
  cout << endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  for(int i = 0; i < t; i++)
    testcase();
  return 0;
}