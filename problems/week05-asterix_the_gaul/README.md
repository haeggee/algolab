Tags: Split and List, Subset Sum

Key ideas:
* Problem ressembles subset sum, with the specialty that we have a constraint sum of items (< T) while only getting a minimum certain amount (>= D)
* --> NP-hard problem, which is why the instances are very small (<= 30)
* for m=0:
  * just enumerate all possible subsets, calculate there sums and check if they satisfy constraints < T and >= D
  * I took the code from the subset sum tutorial slides: the recursive version (which works for testsets 1-3) and an iterative version using bitshifts
* For larger m:
  * We have the invariant that if we take gulp s_j and we have a solution, then we also have a solution for j' >= j
  * hence: can do binary search to find the smallest j, for each choice s_j add the distance to all elements, later subtracting it again
``` 
while(l<=r)
    mid = (l+r)/2
    if(subset_sum_exists) {
        r = mid;
        if(l == r) break;
    } else {
        l = mid + 1;
    }
```
* For latest testcase: need split and list!
  * split the set into two roughly equally sized sets
  * compute the sums of d and sums of t for each set
    * if there already is a solution, can return true
  * sort the 2nd set sums after the time, then do binary search for each value in first set
  * important step: for increasing t, use the maximum sum of d over the smaller t'
    * why? when doing the binary search, we look for the _largest_ t that still fits with sum < T, but we want to maximize the sum D. hence, copy over the max sum_D for t' < t