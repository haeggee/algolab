Tags: Dynamic Programming

Key ideas:
---
* Ugly DP task, with a very complicated DP relation as well as computations...
* essentially, when we define the recursive relation, it depends on
  1. the current fighter next in the queue
  2. the previous fighters north as well as south
  3. the difference in the queues (p-q) (note that the difference is enough, bc. we always just increase and/or decrease it)
* Then, we can decide if we put the next one north or south and, as usual in DP, take the better option depending on the recursive solutions
* The lookup depends on: n, q_north, q_south, diff
  * need to transform them into indices!

Important observations to have compute the indices as well as shrinking the DP table:
1. For the queues:
  * we only need to consider the last two fighters to compute the index - if we consider a single recursive call in isolation, it doesn't matter what the third fighter was because he will be replaced by our choice anyway
  * Considering also the "no fighter" option, we have 5 possible values and 2 positions, hence 25 possibilities
    * can map f1,f2 -> 5 * f1 + f2 (just like in matrix indexing)
  * in total for both queues, gives ~= 625 ~= 6e2
2. For the diff:
  * Given the constraint that at no round the excitement can be negative, we know that the abs(diff) is bounded by 11, as 2^12 = 4096 > 3000, as 3000 is the best excitement
  * Hence, map diff -> diff + 12
  * this dimension is thus ~= 24 ~= 2e1 large
  * Also, don't forget to stop recursion should we reach abs(diff) >= 12


In total, for n <= 5000, we have 5000 * 6e2 * 2e1 ~= 6e7, so feasible enough!

Note that there are other (iterative) solutions using a map and bitshifting to get an integer key, but IMO the classical recursion as here is intuitive.