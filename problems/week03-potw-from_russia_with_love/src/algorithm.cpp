///2

#include <iostream>
#include <vector>
#include <climits>
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

int largest_amount(int k, int m, VVI &memo, VI &v, int  i, int j) {
  if(i == j) { // one coin left
    return v[i];
  } else if (i > j) { // we took the last coin
    return 0;
  } else if(memo[i][j] != -1) { // already computed
    return memo[i][j];
  }
  int min_left = INT_MAX;
  for(int l = 0; l < m; l++) {
    min_left = std::min(min_left, largest_amount(k, m, memo, v, i + 1 + l, j - m + l + 1));
  }
  min_left += v[i];
  
  int min_right = INT_MAX;
  for(int l = 0; l < m; l++) {
    min_right = std::min(min_right, largest_amount(k, m, memo, v, i + l, j - m + l));
  }
  min_right += v[j];
  
  int best = std::max(min_left, min_right);
  memo[i][j] = best;
  return best;
}

void testcase() {
  int n; std::cin >> n;
  int m; std::cin >> m;
  int k; std::cin >> k;
  VI v(n);
  VVI memo(n, VI(n, -1));
  for(int  i = 0; i < n; i++) {
    std::cin >> v[i];
  }
  int best = INT_MAX;
  for(int i = 0; i <= k; i++) {
    best = std::min(best, largest_amount(k, m, memo, v, i, n - k - 1 + i));
  }
  std::cout << best << std::endl;
}


int main() {
  
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t;
  for(int i = 0; i < t; i++) {
    testcase();
  }
}