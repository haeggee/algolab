Tags: MinCost MaxFlow

Key ideas:
* Important: going from top left to bottom right and back is equivalent to going twice down(imagine just inverting the edges)
* a path down can be seen as one unit of flow
* coins can only be collected once, i.e. we need to consider a capacity limit of one per coin
* In fact: it holds that the maximum can be achieved with two node distinct paths
  * to see this: consider a solution where the paths cross at a node. then we can just 'split' the paths in the sense top/bottom of a diagonal; but then, instead of going through the same node twice (and only collecting the coins once), we can take (wlog) the top path and take a detour (collecting at least as much coins) and then consider on the same path
* So, we construct a flow graph:
  * connecting nodes down and right, capacity one (node distinct trivially means edge distinct)
  * edge node has an in and out node to fulfill single collection constraint
  * to have only postive weight: take 100 (the max no. of coins) - a_i,j (to maximize the coins) as the cost between in and out node

Additionally, I dont use the constraint for the top left and bottom right node: bottom right is only an in node + we need two paths from the top left

To get correct cost:
* mincost maxflow from out-node top left to bottom right in-node
* every path has exactly 2 * n - 1 positions, subtracting the start and end node gives 2 * n - 3
* hence, we have 4 * n - 6 nodes on two paths from source to sink
* This gives: (4 * n - 6) * 100 - cost1 + a_00 + a_n-1,n-1