Tags: Delaunay Triangulation, Union Find, Connected Components

Key ideas:
* In my opinion ressemblance to [Idefix](../week11-idefix/), [GoldenEye](../week10-potw-goldeneye/), [Clues](../week13-potw-clues/) just because we rely on the Delaunay Triangulation + Kruskal and Union Find to compute connected components
* For a given squared distance s, one connected component must be assigned to the same family

Hence, general approach: get the delaunay edges, sort them, and while iterating through them (up to a certain point) connect components.


* For task 1: maximal s for which assigning the tents to families f0 is possible s.t. gets >= k tents
  * Iterate through edges and print out the last distance of the last edge added as soon as we create a forest of components that is infeasible with f families
  * for case k=1, this is easy: when n_components < f
  * for generic case, see below
* For task 2: maximal f s.t. all fams have >= k tents and all distances to diff fams >= s
  * Again, iterate through edges and merge components for all edges < s
  * for case k=1 the result is then easy: f is the number of components left (each family gets one)

Generic case k:
* need to optimally assign components to families
* honestly, it's quite a pain to explain in words, e.g.:
  * for k = 3: components of >= 3 + (match 2comp with 1 comp) + remaining2 / 2 + remaining1 / 3