///
#include <iostream>
#include <vector>
#include <climits>


void testcase() {
  int n; std::cin >> n;
  int k; std::cin >> k;
  std::vector<int> v(n);
  std::vector<int> S(n+1);
  int sum = 0;
  int best_i = 0;
  int best_j = 0;
  
  for(int i = 0; i < n; i++) {
      std::cin >> v[i];
      S[i] = sum;
      sum += v[i];
  }
  S[n] = sum;
  
  /////////////////////////////// SLIDING WINDOW
  int best_diff = abs(v[0] - k);
  int l = 0;
  int r = 0;
  int curr_sum = v[0];
  while(l < n && r < n) {
      if(curr_sum == k) {
        break;
      } else if(curr_sum < k) {
        r++;
      } else {
        if(l == r) {
          r++;
        } else {
          l++;
        }
      }
      curr_sum = S[r + 1] - S[l];
      int diff = abs(k - curr_sum);
    
      if(diff < best_diff) {
        // std::cout << "i " << i << " j " << j << " diff " << diff << std::endl;
        best_i = l;
        best_j = r;
        best_diff = diff;
      }
  }
  std::cout << best_i << " " << best_j << std::endl; // Output the final result
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}