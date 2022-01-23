Tags: Binary Search, Delaunay Triangulation, Nearest Neighbor

Key idea: 
  * We have the invariant that if a participant is out after lights [0,i], he will also be out after [0,k] for k >= i.
  * It doesn't matter what round a participant got out, we only care about the _last_ round that participants survived
  * Hence, let's save for each participant the _lowest_ number of rounds that we found where we know for sure that he's out
  * Then, search to find the _lowest_ round i s.t. no one survived rounds [0,i]. Do binary search:
    * Start with interval [0,n-1]: for interval [l,r] and midpoint mid=(l+r)/2, compute Delaunay triangulation for lights [l,mid] (We need this in order to find nearest light for each participant in log(n) time)
    * For each participant, check if he will be out by those lights by checking if the nearest light is < (h+r)^2 away -> if he is out, store mid as his lowest known round to be out
    * If no participant survived, then we know the lowest round i is smaller than mid; set r to mid
    * else, set l = mid + 1
  * At the end, look for the maximum round stored for the participants, and print out those with same number

Runtime: For each loop iteration, have a runtime of O(nlogn + mlogn) (triangulation + m queries for nearest vertex). The binary search is executed O(logn) times, hence overall we have O(logn * (nlogn + mlogn)).

Note: Asymptotically, it does not make a difference to compute the triangulation between [0,mid] or [l,mid], but I got a timeout for the former one!