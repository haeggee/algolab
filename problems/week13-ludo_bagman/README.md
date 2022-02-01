Tags: MinCost MaxFlow, Bipartite Graph

Key ideas:
* Bipartite graph, edges in between are potential matches
* to fulfill at least l matches for each team:
  * edge from source to sink have two paths: one for the l matches for each, one for the rest
   * top path is bottlenecked at e * l, each incoming edge to team has capacity l -->  want a full flow there
   * same goes for sink 
   * forcing the "rest" path to have at max p-e*l matches, we have at least l matches
    for each 
* difficult matches are just a copy of the e+w graph, being connected to the p-e*l bottleneck