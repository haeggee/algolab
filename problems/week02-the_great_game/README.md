Tags: Dynamic Programming

Key ideas:
* two arrays denoting the number of moves needed to get to position n
  * one if we want to maximize number of moves, one for minimizing
* players alternate and want to minimize their own moves while maximizing for the other
* hence for transitions i->j:
  * min_moves[i] = std::min(1 + max_moves[j]);
  * max_moves[i] = std::max(1 + min_moves[j]);
* sherlock wins if (* r and b positions of figures):
  * min_moves[r - 1] < min_moves[b - 1] or
  * (min_moves[r - 1] == min_moves[b - 1] && min_moves[r - 1] % 2 == 1) (since he starts)