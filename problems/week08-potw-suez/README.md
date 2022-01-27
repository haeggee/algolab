Tags: Linear Programming

Key ideas:
* classical LP problem
* want to maximize: sum_{a_i} a_i * 2 * (h + w)
* constraints: posters do not overlap
  * they either hit horizontally or vertically
  * this means: either (ai + aj) * w/2 == abs(xi - xj) or (ai + aj) * h/2 == abs(yi - yj)
  * to find what is the case, the answer is max(2 * abs(xi - xj) / w, 2 * abs(yi - yj) / h)
  * to see this: consider e.g. two posters on a horizontal line -> they will never hit vertically
* for pairs of new posters: no problem, as we have n <= 30, so O(n * 2) constraints is no problem
  * for pairs between new posters and old posters:
    * for all the constraints, there will be a tightest one (i.e. the b in the form of Ax<=b)
    * so just loop over all old posters (in total no more than 10^4 loop iters) and add constraint for the minimum over the maximums
    * otherwise, we would have too many constraints (last test case)

To keep in mind:
* Input type is CGAL::Gmpq because of rationals
* solution in round function needs to use double, as int doesn't fit (I forgot this first, and it actually gave me a timeout on 2 testcases)