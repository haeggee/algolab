#include <iostream>

void testcase() {
  int n; std::cin >> n; // Read the number of integers to follow
  int result = 0; // Variable storing the result
  for (int i = 0; i < n; ++i) {
    int a; std::cin >> a; // Read the next number
    result += a; // Add it to the result
  }
  std::cout << result << std::endl; // Output the final result
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}