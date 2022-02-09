///3
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <limits>

void testcase() {
  size_t n, m, r, b;
  std::cin >> n >> m >> r >> b;
  
  std::vector<size_t> min_moves(n, -1), max_moves(n, -1);
  
  min_moves[n - 1]   = 0;
  max_moves[n - 1]   = 0;
  
  std::vector<std::vector<size_t>> transition(n);
  for(size_t i = 0; i < m; i++) {
    size_t u, v;
    std::cin >> u >> v;
    transition[u-1].push_back(v-1);
  }
  
  for(int i = n - 2; i >= 0; --i) {
    min_moves[i] = std::numeric_limits<size_t>::max();
    max_moves[i] = std::numeric_limits<size_t>::min();
    for(size_t j : transition[i]) {
      min_moves[i] = std::min(min_moves[i], 1 + max_moves[j]);
      max_moves[i] = std::max(max_moves[i], 1 + min_moves[j]);
    }
  }
  
  if(min_moves[r - 1] < min_moves[b - 1] || 
  (min_moves[r - 1] == min_moves[b - 1] && min_moves[r - 1] % 2 == 1)) {
    std::cout << 0 << std::endl;
  } else {
    std::cout << 1 << std::endl;
  }
}

int main() 
{
  std::ios_base::sync_with_stdio(false);
  std::size_t t;
  for (std::cin >> t; t > 0; --t) testcase();
  return 0;
}