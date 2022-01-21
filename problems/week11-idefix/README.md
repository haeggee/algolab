Tags: Delaunay Triangulation, Union-Find, Connected Components, Closest Neighbor 

Key idea: Close relation to Golden Eye problem:
        1:1 correspondence between points being connected (connected components in EMST)
            <==>
            we can move between the disks of the points
            (for a radius >= 2 * minimal distance betw. them) 


Can copy code from the EMST template, and adapt:
* two UF structures, one for given initial radius with s,
    one for radius needed to get k
* for first problem (max bones):
    for each component of tree, store the number of bones reachable
    (i.e. 4 *distance to closest point <= s)
    This can be done via a simple array, as UF comp. have index <= n
    Upon merging, add together the numbers. At the end (when all edges <= s considerd)
    look for max
* for second problem (min. radius b to get k):
    Have additional edges from each bone to closest point with edge weight 4 * dist.
    Sort as usual, then do same procedure as above (i.e. UF) until one comp has >= k bones
    Then the latest edge considered has minimal radius needed

    Why 4 * dist? ->
    for correct b, need to consider radius over all edges, but for edges between trees
    we have that dist = radius / 2. When we sort, we would thus mix up scale