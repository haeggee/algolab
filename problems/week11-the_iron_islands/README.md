Tags: Sliding Window, Prefix Sum, Binary Search, Sorting

Key ideas:
* For a solution to be valid, the set of islands has to be contiguous. 2 cases for that
  * Either it is within a single waterway, or
  * It traverses the island 0 (Pyke) and spreads across 2 waterways
  * More waterways aren't possible
* The first possibility simply boils down to a sliding window solution that looks for an exact sum match
* For the second possibility, we require prefix sums and binary search:
  * First observe: for any solution including the island 0 and going across at least 2 waterways, we have that the interval has value: sum_0^i [0,i'] + sum_0^j [0,j'] - val[0]
  * For each island, we can thus precompute the value from island 0 up to itself
  * Then, for each island we wanna binary search to find the matching value on a different waterway:
    * If we loop over the different pairs of waterways, this becomes too slow (O(n^2))
    * However: we only care about the _longest_ matching other prefix sum
    * Hence: Put them all together in a vector and sort i) first after the prefix sum, and ii) second after the length/distance to island 0
    * Importantly, the binary search is then only with the comparator of the prefix sum
  * Edge case: keep also track of the waterway index when we compare, i.e. to not consider the same waterway. Since the binary search returns the first matching value, we can safely increase the pointer and check if the next key matches