Tags: MinCost MaxFlow, Binary search

Key ideas:
* Model a flow graph with nodes of cities + guides
* For a guide, connect city x-> guide and guide->y. Both edges have capacity e and one of them has cost d, the other zero
* The max flow is limited by the sum of elephants, i.e. we add a source node and connect it with the node k (the initial city) with capacity sum_e
* Then, do binary search to find largest flow s.t. cost <= b:
  * start with bounds [0, initial_max_flow] (computed first for capacity sum_e)
  * in each iteration, change capacity of source->k edge to mid=(l+r) / 2
  * see if cost <= b
* right indices are a bit tricky to get correct IMO:
```
while(l<=r)
    cost = mincost_maxflow(s->a)
    if(cost <= b) { // cost is okay, i.e. go higher
        l = mid + 1;
    } else {
        r = mid;
        if(l == r) break;
    }
    // if we exit loop, l is just one above what is feasible 
```