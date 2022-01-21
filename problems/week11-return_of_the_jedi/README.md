Tags: Minimal Spanning Tree, DFS, 2nd MST

Key idea:
* we look for 2nd best MST
* construct MST with Kruskal
    --> Leias solution (equivalent to her Prim algorithm in terms of weight)
* compute max edge on pairwise paths in MST with DFS in O(n^2) (paths are unique in tree)
* loop through all edges _not_ in MST and
    compute best differences in adding edge (u,v) and
    removing worst edge on MST path between u and v
* WHY? 2nd best MST is attained by adding a single edge that previosuly wasnt in MST
        and then deleting the largest edge in the cycle that is introduced.
* Since the graph is fully connected here, it is more efficient to 
    precompute pairwise max_edge_weights in O(n^2) than to do it for each 
    edge in O(E * V)