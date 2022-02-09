Tags: Sliding Window, Dynamic Programming

Key ideas:
* Sliding window to compute:
  * length array of size n: length of window ending in defender i that has value exactly k
  * -1 if there is no window
* then iterative DP (recursive timed out for me):
  * table of size m * n
  * dp[i][j] : max number of defenders between [0,j] that are attacked
  *  and _all_ attackers up to i are used