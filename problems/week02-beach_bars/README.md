Tags: Sorting, Sliding Window

Key ideas:
* First sort positions
* Then, we know that a solution will cover an interval [i,j] -> use a sliding window approach
* i.e., whenever we consider [i,j] we know that if v[j] - v[i] <= 200, we can cover all positions in between
* since multiple solutions are possible, need to keep track of them with a vector or list
* tricky cases:
  * if (v[i] + v[j]) % 2 != 0, two solutions possible:
    * s1 = v[i] + (v[j] - v[i]) / 2 as well as s1 + 1
  * if the window size is the same, compute these possible solution spots to get the distance and take the new solution in case distance is smaller