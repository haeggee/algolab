Tags: Dynamic Programming, Greedy Search

Key ideas:
* A combination of Dynamic Programming/Precomputation and then greedy search is needed here.
* First: 
  * Note that since the potions of A have 2 different values, they do not have a unique greedy ordering
  * The potions B, however, have one. Just sort after their value w_i
  * Apart from the first test case, sorting potions A thus has no value
* Then we can make the observation: both the number of potions (n <= 100) and the value H are relatively small. Additionally the value H is not negatively affected by potions B
* We can thus make a DP/memory table that still fits in memory and has not too expensive runtime:
  * define dp[i][j][h] as the _largest_ sum of power we can get when taking *j* out of the first *i* potions that have a sum of at least *h*
  * size: 100 ^2 * 2^10 ~= 10^7
  * initialised with all -inf (use long because the sum of powers can be too big for integer)
  * base cases: 
    * for all h, for i>=1, j==1:
      * take the highest power potions that fulfills h
      * dp[i][1][h] = pots_a[i-1].h >= h ? max(dp[i-1][1][h], pots_a[i - 1].p) : dp[i-1][1][h];
    * then, increasing j>=2, h, i>=j:
      * either the previous value without potions i was better, or we take it and can add its power to the value of i-1, j-1, and fulfilling the h-offest
      * int prev_h = max(0, h - pots_a[i-1].h);
      * dp[i][j][h] = max(dp[i-1][j][h], dp[i-1][j-1][prev_h] + pots_a[i-1].p);
* Having filled out the DP table, we e.g. know that we can search for the smallest j for which dp[n][j][H]>=P in order to have the minimum of potions to fulfill P and H

To combine it with the potions of B, do a greedy search:
* We take more and more potions B (sorted by their w_i), compute the current wit w that we get as well as the decrease in power via (#pot * b)
* For a certain number of potions, we search for increasing j in our DP table:
  * We cannot take too many j that decrease the current wit too much (offset j * a)
  * While wit is okay, we search for the first j where dp[n][j][H] >= P + (#potB * b)
* We know that the first time this conditions if fulfilled, we have the minimum potions! That is because we increase the #potB and look for the smallest j for each iteration - there cannot be a smaller sum of those values in a later iteration