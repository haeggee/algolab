Tags: Recursion, Tree, Greedy

Key ideas:
* We have a tree structure
* can do recursive traversal to get best result
* Main challenge: finding best solution in subquadratic time at each point in recursion


Solution:
* recurse with three values:
  1. max number of gold one can collect in the subtree (neglecting any kind of offset at the beginning, i.e. only take into account traversal time inside subtree)
  2. number of nodes in subtree
  3. full traversal time
* we can recursively solve, for each recursive solution add 2*l to traversal time (going to and back subtree/edge) and subtract the gold we loose: (#nodes in subtree * l)
* sort the results: r1.traversal_time * r2.num_nodes < r2.traversal_time * r1.num_nodes
* i.e. greedily take the subtree where we loose the least number of gold!
  * why is this correct?
    * we have the assumption that no matter what traversal, there will always be a bit of gold
    * i.e. we always collect nonzero gold!
    * effectively, what we get is then #sum of all gold - #sum of gold lost
    * --> try to minimize the right term
* For the first few testcases, it suffices to sort after the traversal time