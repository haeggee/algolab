Tags: Prefix Sum

Same concept as Even Pairs, just 2 dimensions. Overall runtime O(n^3)

* compute the prefixes in quadratic time
  * S[i + 1][j + 1] = S[i + 1][j] + S[i][j + 1] - S[i][j] + v[i][j];
* For interval (i1,i2,j1,j2): value is S[i2,j2] - S[i2,j1] - S[i1,j2] + S[i1,j1]
* Then, if we fix a range [i1,i2]:
  * problem becomes the same as even pairs
  * can linearly (for j) compute the expression above and count even and uneven sums