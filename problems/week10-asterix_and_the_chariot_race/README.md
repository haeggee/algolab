Tags: DFS, Tree, Recursion

IDEA:
    do dfs starting from root node 0 (as we have a tree)
    and recursively solve - we always have 3 cases, as explained below
return 3 optimal values:
- 0: opt cost if this node is definitely taken
- 1: opt cost if this node is covered by parent, but might still be taken
- 2: opt cost if this node is _not_ covered by parent, but might still be taken
 
then for current node, we have: 
- selected opt    = cost[v] + sum_covered
- covered opt     = min(sum_not_covered, self_selected)
- not covered opt = min(sum_not_covered + best_diff, self_selected)