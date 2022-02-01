#include <iostream>
#include <vector>

void testcase() {
  int n; std::cin >> n; // Read the number of integers to follow
  std::vector<int> v(n);
  int sum = 0;
  int num_even = 0;
  int num_uneven = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> v[i]; // Read the next number
    sum += v[i];
    if(sum % 2 == 0) {
      ++num_even;
    } else {
      ++num_uneven;
    }
  }
  int result = num_even * (num_even - 1) / 2;
  result += num_uneven * (num_uneven - 1) / 2;
  result += num_even;
  
  std::cout << result << std::endl; // Output the final result
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}