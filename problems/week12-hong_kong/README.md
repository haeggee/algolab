Tags: Delaunay Triangulation, DFS/BFS, Priority Queue, Dijkstra, Circle/Radius computation

Key Idea: Same skeleton and concept as [H1N1](../week8-h1n1/). What is different:
* We can also escape inside the convex hull of the points, but for that need a larger distance to all points
* These safe spots can just be boiled down to the centers of the Voronoi faces
  * _However_: Do not need to compute the exact points, but just the radius of the circle induced by the triangles. The radius describes the distance to the 3 points
* As we have the requirement that the **circles** (as geometric objects) of the balloons and trees are r + s_i apart, we essentially have that the center points need to be 2*(r + s_i) apart.
* Hence, we can just initially add the radii of the triangles to the priority queue (no additional multiplicative factor), since the constraint is exactly the same as when moving between faces/along the edges   