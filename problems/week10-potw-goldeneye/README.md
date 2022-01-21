Tags: Delaunay Triangulation, Union-Find, Connected Components, Closest Neighbor 

Key idea: 

1:1 correspondence between points being connected (connected components in EMST) <==>

we can move between the disks of the points (for a radius >= 2 * minimal distance betw. them) 


Can copy code from the EMST template, and adapt:
* three UF structures, one for the given radius U_p,
    U_a: minimum power needed to execute _all_ missions
    U_b: minimum power needed to execute same set of missions as with inital p
* First connect components of U_p with edges <= p
* then see, for each mission, if 4*distance <= p and
    components are connected, mission can be executed
* If can be executed: enlarge U_b until it is covered
* In any case: enlarge U_a until it is covered