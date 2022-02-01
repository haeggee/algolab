#include <iostream>
#include <vector>

void testcase() {
  int n; std::cin >> n; // Read the number of integers to follow
  std::vector<int> h(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> h[i]; // Read the next number
  }
  
  int num_tiles = 1;
  for (int i = 0; i < n; ++i) {
    if((i+1) <= num_tiles) {
      num_tiles = std::max(num_tiles, i + h[i]);
    }
  }
  
  std::cout << std::min(num_tiles, n) << std::endl; // Output the final result
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}