#include <iostream>
#include <vector>
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;


// S[i2,j2] - S[i2,j1] - S[i1,j2] + S[i1,j1]
void testcase() {
  int n; std::cin >> n; // Read the number of integers to follow
  VVI v(n, VI(n));
  VVI S(n + 1, VI(n + 1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int x; std::cin >> x; // Read the next number
      v[i][j] = x;
      S[i + 1][j + 1] = S[i + 1][j] + S[i][j + 1] - S[i][j] + v[i][j];
      // std::cout << S[i + 1][j + 1] << " ";
    }
  // std::cout << std::endl;
  }


  int result = 0;
  for (int i1 = 1; i1 < n + 1; ++i1) {
      for (int i2 = i1; i2 < n + 1; ++i2) {
        int even = 0;
        int uneven = 0;
        for (int j = 1; j < n + 1; ++j) {
            int res = S[i2][j] - S[i1-1][j];
            if(res % 2 == 0) {
                ++even;
            } else {
                ++uneven;
            }
        }
        result += even * (even - 1) / 2 + uneven * (uneven - 1) / 2 + even;
    }
  }
  std::cout << result << std::endl; // Output the final result
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}
