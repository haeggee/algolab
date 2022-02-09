Tags: Dynamic Programming

Key ideas:
* Classical DP: either take left or right, but the recursion repeats itself for [i,j] coins left
* i.e., DP table of size n * n
* in order to consider "guaranteed" amount, asssume other player is _minimizing_ your return
* Denote the possibilities l_r == you take left, other player takes right, and accordingly for the other options. 
  * recursion is thus: max(min(l_r, l_l) + v[i], min(r_r, r_l) + v[j]);