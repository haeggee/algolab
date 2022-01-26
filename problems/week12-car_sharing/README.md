Tags: MinCost MaxFlow, Maps

Key ideas:
* Space-time graph, i.e. duplicating the stations across times
* connections between timesteps are either from same station to same station with zero weight, or the requests with the profit as negative weight
* then: can be solved as MinCost MaxFlow problem, connecting the stations at timestep 0 with source with num. cars as capacity

Challenges here:
* transform negative weights into positive weights by applying the transform: Max_P * (distance in time) - actual_weight, i.e. the prices. same goes for zero edge weights (car staying in a station) -> this will have all s-t paths with the same costs before and after
* do not construct full graph over all timesteps, but only consider timesteps where we actually have requests -> store a map for each station, with keys timesteps and mapping to indices in flow graph