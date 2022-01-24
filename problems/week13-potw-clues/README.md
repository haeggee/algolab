Tags: Delaunay Triangulation, Bipartite Graph, Minimal Spanning Tree, Connected Components

Key ideas:
---
The problem boils down to 2 things: i) checking if an (implicit) graph is bipartite and ii) if the queried points are connected via the network of points. I choose to make use of BGL instead of implementing BFS and other things from scratch.

1. To me, the connection of query points is a simpler problem.
   * We know that points with distance <= r are connected. In close relation to [GoldenEye](../week10-potw-goldeneye/) and [Idefix](../week11-idefix/) (where we used Union Find) we thus look at the EMST with edges <= r and the connected components (I use BGL, as might become clear below when getting the coloring too). Assuming the graph of points is bipartite (e.g. testcases 2 and 3), we differ:
     * dist(a,b) <= r : simply output yes
     * the closest points of the network/triangulation are too far away for either one a or b: output no
     * otherwise, we check if the two closest points in the network are in the same component
2. Bipartite: 
   * Important note: for the input size, the runtime cannot be O(n^2) - this also tells us that we cannot explicitly create the graph representing connected points, because in a worst case it is fully connected
   * Somehow obvious and already from the connection problem above, we compute a Delaunay triangulation of the network points
   * The forest of trees given by the Delaunay triangulation already has to be bipartite! Hence:
     * Check bipartiteness of the graph given by the Delaunay edges <= r and get the coloring white/black if true
     * Then: we can use the coloring found by BGL to split the points into two sets and create one triangulation for each color. Since the Delaunay triangulation again includes the closest neighbor for each point, we have that all edges must be larger than r! I.e. looping through all edges and breaking the loop for a violation suffices  
   * To see why this guarantees and if and only if relation to the points being bipartite: The triangulation + EMST is guaranteed to find the connected components (since nearest neighbors <= r edges are added). For a connected component in a bipartite graph, _removing_ edges while staying connected cannot change the color assignments. But when we add edges (as in the case of the two additional triangulations), we can detect violations of bipartiteness
    
