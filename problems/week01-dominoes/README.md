Key ideas:
* linearly go through array, always remember the furthest we can go
  * if i+1 <= curr_est_tiles, this dominoe will also be tipped
  * then: max(curr_est, i + h[i])
* end result is min(n, estimate)