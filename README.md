# Algolab 2021
My code for the problems given in the ETH course [Algorithms Lab in Fall 2021](https://www.cadmo.ethz.ch/education/lectures/HS21/algolab/index.html). Problems descriptions and testcases not included. I did not put as much effort into this as [this guy](https://github.com/simon-hrabec/algolab-2020) did, but I took some inspiration :) Also credits to the creators of the [algolabVS.sh](algolabVS.sh) with which this stuff was done (+ Code Expert).


## Problems sorted by weeks
| Week | Problem of the Week                                                   | 1st problem                                                                  | 2nd problem                                              | 3rd problem                                    | 4th problem                                                        |
| ---- | --------------------------------------------------------------------- | ---------------------------------------------------------------------------- | -------------------------------------------------------- | ---------------------------------------------- | ------------------------------------------------------------------ |
| 1    | -                                                                     | [Build the sum](problems/)                                                   | [Dominoes](problems/)                                    | [Even Pairs](problems/)                        | [Even Matrices](problems/)                                         |
| 2    | [Deck of Cards](problems/)                                            | [Beach Bars](problems/)                                                      | [Burning Coins](problems/)                               | [The Great Game](problems/)                    | [Defensive Line](problems/)                                        |
| 3    | [From Russia with Love](problems/)                                    | [First Hit](problems/)                                                       | [Hit](problems/)                                         | [Antenna](problems/)                           | [Hiking Maps](problems/)                                           |
| 4    | [Fighting Pits of Meereen](problems/week04-potw-fighting_pits_mereen) | [First steps with BGL](problems/)                                            | [Important Bridges](problems/)                           | [Buddy Selection](problems/)                   | [Ant Challenge](problems/)                                         |
| 5    | [Motorcycles](problems/)                                              | [Boats](problems/week05-boats)                                               | [Moving Books](problems/week05-moving_books)             | [Severus Snape](problems/week05-severus_snape) | [Asterix and the Gaul](problems/week05-asterix_the_gaul/)          |
| 6    | [Planet Express](problems/)                                           | [isdf](problems/)                                                            | [Inball](problems/week06-inball)                         | [Dominoes](problems/)                          | [Dominoes](problems/)                                              |
| 7    | [Octopussy](problems/)                                                | [isdf](problems/)                                                            | [Dominoes](problems/)                                    | [Dominoes](problems/)                          | [Dominoes](problems/)                                              |
| 8    | [Suez](problems/week08-potw-suez)                                     | [isdf](problems/)                                                            | [Dominoes](problems/)                                    | [H1N1](problems/week08-h1n1)                   | [Light the Stage](problems/week08-light_the_stage)                 |
| 9    | [Kingdom Defence](problems/)                                          | [isdf](problems/)                                                            | [Dominoes](problems/)                                    | [Dominoes](problems/)                          | [Dominoes](problems/)                                              |
| 10   | [GoldenEye](problems/week10-potw-goldeneye/)                          | [Asterix and the Chariot Race](problems/week10-asterix_and_the_chariot_race) | [Dominoes](problems/)                                    | [Dominoes](problems/)                          | [Dominoes](problems/)                                              |
| 11   | [Phantom Menace](problems/)                                           | [The Iron Islands](problems/week11-the_iron_islands)                         | [Return of the Jedi](problems/week11-return_of_the_jedi) | [Idefix](problems/week11-idefix/)              | [Asterix and the Legions](problems/week11-asterix_and_the_legions) |
| 12   | [San Francisco](problems/week12-potw-san_francisco)                   | [Majesty's service](problems/week12-majestys_secret_service)                 | [Hong Kong](problems/week12-hong_kong)                   | [Carsharing](/problems/week12-car_sharing)     | [Bonus Level](problems/week12-bonus_level)                         |
| 13   | [Clues](problems/week13-potw-clues)                                   | [Hagrid](problems/week13-hagrid)                                             | [Punch](problems/week13-punch)                           | [Hand](problems/week13-hand)                   | [Ludo Bagman](problems/week13-ludo_bagman)                         |
| 14   | [India](problems/week14-potw-india)                                   |                                                                              |                                                          |                                                |                                                                    |


# !! SPOILERS AHEAD
# 
# 

## Categorizing solutions, techniques, properties and algorithms
| Properties, Technique, Data Structure, Algorithm   | Problems                                                                                                                                                                                                                                                                                                                   |
| -------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| BFS                                                |                                                                                                                                                                                                                                                                                                                            |
| (Bi)connected Components                           | [Clues](problems/week13-potw-clues), [Hand](problems/week13-hand)                                                                                                                                                                                                                                                          |
| Binary Search                                      | [H1N1](problems/week08-h1n1), [Light the Stage](problems/week08-light_the_stage), [Idefix](problems/week11-idefix/), [GoldenEye](problems/week10-potw-goldeneye/), [India](problems/week14-potw-india), [Majesty's service](problems/week12-majestys_secret_service), [The Iron Islands](problems/week11-the_iron_islands) |
| CGAL Geometry                                      | [Hong Kong](problems/week12-hong_kong)                                                                                                                                                                                                                                                                                     |
| CGAL::Gmpq/Gmpz, K::FT (Arbitrary Precision Types) | [Hong Kong](problems/week12-hong_kong)                                                                                                                                                                                                                                                                                     |
| DFS                                                | [Asterix and the Chariot Race](problems/week10-asterix_and_the_chariot_race), [Return of the Jedi](problems/week11-return_of_the_jedi)                                                                                                                                                                                     |
| Delaunay Triangulation                             | [Idefix](problems/week11-idefix/), [GoldenEye](problems/week10-potw-goldeneye/), [H1N1](problems/week08-h1n1), [Light the Stage](problems/week08-light_the_stage), [Clues](problems/week13-potw-clues), [Hong Kong](problems/week12-hong_kong), [Hand](problems/week13-hand)                                               |
| Dijkstra                                           | [Hong Kong](problems/week12-hong_kong), [H1N1](problems/week08-h1n1), [Majesty's service](problems/week12-majestys_secret_service)                                                                                                                                                                                         |
| Dynamic Programming                                | [Fighting Pits of Meereen](problems/week04-potw-fighting_pits_mereen), [Severus Snape](problems/week05-severus_snape), [San Francisco](problems/week12-potw-san_francisco), [Punch](problems/week13-punch)                                                                                                                 |
| Graph Duplication                                  | [Carsharing](/problems/week12-car_sharing)                                                                                                                                                                                                                                                                                 |
| Greedy                                             | [Severus Snape](problems/week05-severus_snape), [Hagrid](problems/week13-hagrid)                                                                                                                                                                                                                                           |
| Kruskal                                            | [Idefix](problems/week11-idefix/), [GoldenEye](problems/week10-potw-goldeneye/), [Return of the Jedi](problems/week11-return_of_the_jedi), [Hand](problems/week13-hand)                                                                                                                                                    |
| Linear Programming                                 | [Suez](problems/week08-potw-suez), [Inball](problems/week06-inball), [Asterix and the Legions](problems/week11-asterix_and_the_legions)                                                                                                                                                                                    |
| Max-Flow-Min-Cost                                  | [Bonus Level](problems/week12-bonus_level), [Carsharing](/problems/week12-car_sharing), [India](problems/week14-potw-india), [Ludo Bagman](problems/week13-ludo_bagman)                                                                                                                                                    |
| Maximum Flow                                       | [Majesty's service](problems/week12-majestys_secret_service)                                                                                                                                                                                                                                                               |
| Maximum Matching                                   | [Majesty's service](problems/week12-majestys_secret_service)                                                                                                                                                                                                                                                               |
| Minimum Spanning Tree                              | [Clues](problems/week13-potw-clues), [Return of the Jedi](problems/week11-return_of_the_jedi), [Hong Kong](problems/week12-hong_kong), [Idefix](problems/week11-idefix/), [GoldenEye](problems/week10-potw-goldeneye/), [H1N1](problems/week08-h1n1), [Hand](problems/week13-hand)                                         |
| Prefix Sum                                         | [The Iron Islands](problems/week11-the_iron_islands)                                                                                                                                                                                                                                                                       |
| Randomization                                      |                                                                                                                                                                                                                                                                                                                            |
| Recursion                                          | [Asterix and the Chariot Race](problems/week10-asterix_and_the_chariot_race), [Hagrid](problems/week13-hagrid)                                                                                                                                                                                                             |
| Sliding Window                                     | [The Iron Islands](problems/week11-the_iron_islands)                                                                                                                                                                                                                                                                       |
| Sorting                                            | [The Iron Islands](problems/week11-the_iron_islands)                                                                                                                                                                                                                                                                       |
| Split and List                                     | [Asterix and the Gaul](problems/week05-asterix_the_gaul/)                                                                                                                                                                                                                                                                  |
| Tree                                               | [Asterix and the Chariot Race](problems/week10-asterix_and_the_chariot_race), [Hagrid](problems/week13-hagrid)                                                                                                                                                                                                             |
| Union-Find                                         | [Idefix](problems/week11-idefix/), [GoldenEye](problems/week10-potw-goldeneye/), [Hand](problems/week13-hand)                                                                                                                                                                                                              |