#include <iostream>
#include <vector>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

int largest_amount(VVI &m, VI &v, int  i, int j) {
  if(i == j) { // one coin left
    return v[i];
  } else if (i > j) { // we took the last coin
    return 0;
  } else if(m[i][j] != -1) { // already computed
    return m[i][j];
  }
  int l_r = largest_amount(m, v, i + 1, j - 1);
  int l_l = largest_amount(m, v, i + 2, j);
  int r_l = largest_amount(m, v, i + 1, j - 1);
  int r_r = largest_amount(m, v, i, j - 2);
  int min_left = std::min(l_r, l_l);
  int min_right = std::min(r_l, r_r);
  int best = std::max(min_left + v[i], min_right + v[j]);
  m[i][j] = best;
  return best;
}

void testcase() {
  int n; std::cin >> n;
  VI v(n);
  VVI m(n, VI(n, -1));
  for(int  i = 0; i < n; i++) {
    std::cin >> v[i];
  }
  std::cout << largest_amount(m, v, 0, n - 1) << std::endl;
}


int main() {
  
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t;
  for(int i = 0; i < t; i++) {
    testcase();
  }
}