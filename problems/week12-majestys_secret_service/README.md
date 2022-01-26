Tags: Dijkstra, Shortest Path, Bipartite Graph, Maximum Matching, MaxFlow

Key ideas:
* Consider case c=1: Every shelter hosts exactly one agent, i.e. we basically have a matching relation between agents <-> shelters
  * for a given matching, the bottleneck is the agent that takes the _longest_ to reach a shelter
  * **Minimum Bottleneck Matching**
  * Can construct a bipartite graph with agents <-> shelters, with edges in between the nodes if an agent can reach a shelter
  * No matter what shelter an agent goes to, however, he should take the _shortest_ route to it (minimizing the bottleneck)
  * To extract distances: perform Dijkstra for every agent (which gets us the minimum distances to all shelters)
* Then, the task of finding the minimum time needed by searching for the smallest t s.t. matching of size a (number of agents) still possible, i.e. we only add edges with distance(a_i->s_j) + d <= t
  * Perform binary search for this! bounded by log(max_dist + d), which is in the order of log(n * max_z)
* To get maximum matching, can use MaxFlow for bipartite graph


How to generalize to c=2?
* If an agent reaches a shelter while another one enters (does the protocol), he will have to wait <= d time (equality only in case they both arrive at the same time)
* i.e., if for every matching agent -> 2nd slot in shelter, his time to enter is upper bounded by distance + 2 * d
* Thus:
  * Add a copy of the shelters to bipartite graph representing the 2nd slots
  * Connect agent with _copy_ of shelters if distance + 2 * d <= t
  * Compute matching as usual, see if it has cardinality a
  * (Factually, the copies of shelters represent the first slot. Consider: an agent a1 is assigned to a shelter of the first set s1, and another agent a2 is assigned to the same shelter but in s2,and a1 has no edge to s2. Then we know that dist2+2*d <= dist1+d, i.e. dist2+d <= dist1. This then tells us that a1 will wait for a2 to finish, and then we add d to get the bottleneck waiting time)