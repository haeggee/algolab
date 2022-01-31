Tags: Dynamic Programming

Key ideas:
* Directly ressembles DP task with different beverages, being able to take them or not
* Difference to other recursion/DP tasks that are similar: we can take a beverage multiple times
* Summarized:
  * DP table of size n * k that describes the minimum cost
    * additionally, return the max. distinct beverages for a min cost
  * recursion: for dp[i][k], either:
    * do not take beverage i, i.e. dp[i-1][k]
    * or take beverage i **at least** once, i.e. cost[i] + d[i-1][k-vol[i]
  * additionally, to keep track of _distinct_ beverages, return if beverage i was actually taken in solution dp[i][k]
  * then, to break ties, take beverage if:
    * take if strict minimal cost (c' < c)
    * if same cost, take if dist. beverages are strictly higher
    * do not take if same cost, same beverages (this could lead to more distinct beverages downstream/in a higher recursive call)