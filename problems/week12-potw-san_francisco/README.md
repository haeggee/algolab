Tags: Dynamic Programming, Graph

Key Ideas:
* DP table of size [n,k] to represent the max score starting from node i after j moves
* recursion relation: score[i, j+1] = max over edges( score[i, j] + edge from i to v)
* for nodes with no outgoing edges, take the score of node 0 (the source). have to make sure that the loop has filled out the score[0, j+1] first