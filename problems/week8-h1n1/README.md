Tags: Delaunay Triangulation, DFS, BFS, Minimal Spanning Tree

Key ideas:
 * For each route request, can consider:
   * 1: closest point of infected is too close (sq. dist < d), so "n"
   * 2: otherwise: we can move to any edge of the Voronoi diagram of that is adjacent to this face.
 * In case of 2, the question then becomes: moving along the edges of the Voronoi diagram, we want to reach the infinite face (i.e. going outside the convex hull). For this to be possible, we need a path from the current face to the infinite face. We have a graph problem with the faces being the nodes and edges encoding adjacency of triangles/faces.
 * Moving along one Voronoi edge means passing between two infected points. Hence, for a person to escape, we need that all distances between infected points (that is, the length of the edge of the triangulation) on a path to freedom is >= 4 * d 
 * As a precomputation, we can compute the _best bottleneck_ to move out for any face f. In complicated words: the maximal minimal distance along any path from f to the infinite face
 * Note here that this best bottleneck is upper bounded by the edges of the convex hull! That is, all bottlenecks are smaller or equal to the max. width from the outer faces to the infinite face
 * Algorithm
   * Construct graph with edge weights being distances
   * Use priority queue to propagate the bottlenecks:
     * Starting from infinite face, put on priority queue the minimum of (this faces' bottleneck, edge weight)
     * queue is giving max. distance
   * Then for any query, it's a simple check of the 2 points: if sq.dist < d, then "n", otherwise bottleneck < 4 * d ? "n" : "y" 