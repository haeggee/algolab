#include <vector>
#include <iostream>

int dp[101][100'001];
int len[100'001];

int solve(std::vector<std::vector<int>> &dp, size_t att_i, size_t def_j) {
  // std::cerr << att_i << " " << def_j << "\n";
  if(att_i == 0) {
    return 0;
  }
  if(def_j == 0) {
    return -1;
  }
  
  if(dp[att_i][def_j] != -1) {
    return dp[att_i][def_j];
  }
  
  
  int len_at = len[def_j - 1];
  if(len_at != -1) {
    int prev_res = solve(dp, att_i - 1, def_j - len_at);
    if(prev_res != -1) {
      dp[att_i][def_j] =
        std::max(prev_res + len_at, solve(dp, att_i, def_j - 1));
      return dp[att_i][def_j];
    }
  } 
  
  dp[att_i][def_j] = solve(dp, att_i, def_j - 1);
  return dp[att_i][def_j];
}

void testcase() {
  int n, m, k;
  std::cin >> n >> m >> k;
  
  std::vector<size_t> v(n);
  // std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, -1));
  
  for(int i = 0; i < n; i++) {
    std::cin >> v[i];
    // len: length of window ending in i that has value exactly k,
    //      -1 if there is no window
    len[i] = -1;
  }
  
  int l = 0;
  int r = 0;
  int sum = v[l];
  while(l < n) {
    if(sum == k) {
      len[r] = r - l + 1;
      sum -= v[l];
      ++l;
      if(l == n) break;
    } else if(sum < k) {
      ++r;
      if(r == n) {
        break;
      }
      sum += v[r];
    } else {
      sum -= v[l];
      ++l;
      if(l > r) {
        if(l == n) break;
        sum = v[l];
        r = l;
      }
    }
  }
  
  for(int i = 0; i <= n; i++) {
    dp[0][i] = 0;
    // if(i < n) std::cerr << len[i] << " ";
  }
  for(int i = 1; i <= m; i++) {
    dp[i][0] = -1;
  }

  // dp[i][j] : max number of defenders between [0,j] that are attacked
  //            and _all_ attackers up to i are used
  for(int i = 1; i <= m; i++) {
    for(int j = 1; j <= n; j++) {
      const int len_at = len[j-1];
      if (len_at != -1 && dp[i-1][j-len_at] != -1) {
        dp[i][j] = std::max(dp[i-1][j-len_at] + len_at, dp[i][j-1]);
      } else {
        dp[i][j] = dp[i][j-1];  
      }
    }
  }

  // std::cerr << "\n";
  const int res = dp[m][n];
  
  // timelimit for the recursive one
  // int res = solve(dp, m, n);
  if(res != -1) {
    std::cout << res << "\n";
    return;
  }
  std::cout << "fail" << std::endl;
}

int main() 
{
  std::ios_base::sync_with_stdio(false);
  std::size_t t;
  for (std::cin >> t; t > 0; --t) testcase();
  return 0;
}