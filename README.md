# Algolab 2021
My code for the problems given in the ETH course [Algorithms Lab in Fall 2021](https://www.cadmo.ethz.ch/education/lectures/HS21/algolab/index.html). Problems descriptions and testcases not included. I did not put as much effort into this as [this guy](https://github.com/simon-hrabec/algolab-2020) did, but I took some inspiration :) Also credits to the creators of the [algolabVS.sh](algolabVS.sh) with which this stuff was done (+ Code Expert).

Code requires C++, CGAL, BGL. See https://cadmo.ethz.ch/education/lectures/HS21/algolab/technical.html.

E.g. on Ubuntu, run
```
sudo apt-get install build-essential libboost-all-dev libcgal-dev cmake cmake-data
```

## Problems sorted by weeks
| Week | Problem of the Week                                                   | 1st problem                                                                  | 2nd problem                                                | 3rd problem                                                       | 4th problem                                                        |
| ---- | --------------------------------------------------------------------- | ---------------------------------------------------------------------------- | ---------------------------------------------------------- | ----------------------------------------------------------------- | ------------------------------------------------------------------ |
| 1    | -                                                                     | [Build the sum](problems/week01-build_the_sum)                               | [Dominoes](problems/week01-dominoes)                       | [Even Pairs](problems/week01-even_pairs)                          | [Even Matrices](problems/week01-even_matrices)                     |
| 2    | [Deck of Cards](problems/week02-potw-deck_of_cards)                   | [Beach Bars](problems/week02-beach_bars)                                     | [Burning Coins](problems/week02-burning_coins)             | [The Great Game](problems/week02-the_great_game)                  | [Defensive Line](problems/week02-defensive_line)                   |
| 3    | [From Russia with Love](problems/week03-potw-from_russia_with_love)   | [First Hit](problems/week03-first_hit)                                       | [Hit](problems/week03-hit)                                 | [Antenna](problems/week03-antenna)                                | [Hiking Maps](problems/week03-hiking_maps)                         |
| 4    | [Fighting Pits of Meereen](problems/week04-potw-fighting_pits_mereen) | [First steps with BGL](problems/week04-first_steps_bgl)                      | [Important Bridges](problems/week04-important_bridges)     | [Buddy Selection](problems/week04-buddy_selection)                | [Ant Challenge](problems/week04-ant_challenge)                     |
| 5    | [Motorcycles](problems/week05-potw-motorcycles)                       | [Boats](problems/week05-boats)                                               | [Moving Books](problems/week05-moving_books)               | [Severus Snape](problems/week05-severus_snape)                    | [Asterix and the Gaul](problems/week05-asterix_the_gaul/)          |
| 6    | [Planet Express](problems/week06-potw-planet_express)                 | [Maximize it](problems/week06-maximize_it)                                   | [Inball](problems/week06-inball)                           | [Diet](problems/week06-diet)                                      | [Lannister](problems/week06-lannister)                             |
| 7    | [Octopussy](problems/week07-potw-octopussy)                           | [Shopping Trip](problems/week07-shopping_trip/)                              | [Knights](problems/week07-knights)                         | [Coin Tossing](problems/week07-coin_tossing)                      | [London](problems/week07-london)                                   |
| 8    | [Suez](problems/week08-potw-suez)                                     | [Bistro](problems/week08-bistro)                                             | [Germs](problems/week08-germs)                             | [H1N1](problems/week08-h1n1)                                      | [Light the Stage](problems/week08-light_the_stage)                 |
| 9    | [Kingdom Defence](problems/week09-potw-kingdom_defence)               | [Real Estate Market](problems/week09-real_estate)                            | [Placing Knights](problems/week09-placing_knights)         | [Algocoon Group](problems/week09-algocoon_group/)                 | [Canteen](problems/week09-canteen/)                                |
| 10   | [GoldenEye](problems/week10-potw-goldeneye/)                          | [Asterix and the Chariot Race](problems/week10-asterix_and_the_chariot_race) | [World Cup](problem/week10/../../problems/week10-worldcup) | [Asterix in Switzerland](problems/week10-asterix_in_switzerland/) | [Evolution](problems/week10-evolution/)                            |
| 11   | [Phantom Menace](problems/week11-potw-phantom_menace/)                | [The Iron Islands](problems/week11-the_iron_islands)                         | [Return of the Jedi](problems/week11-return_of_the_jedi)   | [Idefix](problems/week11-idefix/)                                 | [Asterix and the Legions](problems/week11-asterix_and_the_legions) |
| 12   | [San Francisco](problems/week12-potw-san_francisco)                   | [Majesty's service](problems/week12-majestys_secret_service)                 | [Hong Kong](problems/week12-hong_kong)                     | [Carsharing](/problems/week12-car_sharing)                        | [Bonus Level](problems/week12-bonus_level)                         |
| 13   | [Clues](problems/week13-potw-clues)                                   | [Hagrid](problems/week13-hagrid)                                             | [Punch](problems/week13-punch)                             | [Hand](problems/week13-hand)                                      | [Ludo Bagman](problems/week13-ludo_bagman)                         |
| 14   | [India](problems/week14-potw-india)                                   |                                                                              |                                                            |                                                                   |                                                                    |


# !! SPOILERS AHEAD
# 
# 

## Categorizing solutions, techniques, properties and algorithms
| Properties, Technique, Data Structure, Algorithm   | Problems                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| -------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| BFS                                                |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            |
| (Bi)connected Components                           | [Clues](problems/week13-potw-clues), [Hand](problems/week13-hand)                                                                                                                                                                                                                                                                                                                                                                                                                          |
| Binary Search                                      | [H1N1](problems/week08-h1n1), [Light the Stage](problems/week08-light_the_stage), [Idefix](problems/week11-idefix/), [GoldenEye](problems/week10-potw-goldeneye/), [India](problems/week14-potw-india), [Majesty's service](problems/week12-majestys_secret_service), [The Iron Islands](problems/week11-the_iron_islands)                                                                                                                                                                 |
| CGAL Geometry                                      | [Hong Kong](problems/week12-hong_kong)                                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| CGAL::Gmpq/Gmpz, K::FT (Arbitrary Precision Types) | [Hong Kong](problems/week12-hong_kong)                                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| DFS                                                | [Asterix and the Chariot Race](problems/week10-asterix_and_the_chariot_race), [Return of the Jedi](problems/week11-return_of_the_jedi)                                                                                                                                                                                                                                                                                                                                                     |
| Delaunay Triangulation                             | [Idefix](problems/week11-idefix/), [GoldenEye](problems/week10-potw-goldeneye/), [H1N1](problems/week08-h1n1), [Light the Stage](problems/week08-light_the_stage), [Clues](problems/week13-potw-clues), [Hong Kong](problems/week12-hong_kong), [Hand](problems/week13-hand)                                                                                                                                                                                                               |
| Dijkstra                                           | [Hong Kong](problems/week12-hong_kong), [H1N1](problems/week08-h1n1), [Majesty's service](problems/week12-majestys_secret_service)                                                                                                                                                                                                                                                                                                                                                         |
| Dynamic Programming                                | [Beach Bars](problems/week02-beach_bars), [Burning Coins](problems/week02-burning_coins)             , [The Great Game](problems/week02-the_great_game), [Defensive Line](problems/week02-defensive_line), [Fighting Pits of Meereen](problems/week04-potw-fighting_pits_mereen), [Severus Snape](problems/week05-severus_snape), [San Francisco](problems/week12-potw-san_francisco), [Punch](problems/week13-punch), [From Russia with Love](problems/week03-potw-from_russia_with_love) |
| Graph Duplication                                  | [Carsharing](/problems/week12-car_sharing)                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| Greedy                                             | [Severus Snape](problems/week05-severus_snape), [Hagrid](problems/week13-hagrid)                                                                                                                                                                                                                                                                                                                                                                                                           |
| Kruskal                                            | [Idefix](problems/week11-idefix/), [GoldenEye](problems/week10-potw-goldeneye/), [Return of the Jedi](problems/week11-return_of_the_jedi), [Hand](problems/week13-hand)                                                                                                                                                                                                                                                                                                                    |
| Linear Programming                                 | [Suez](problems/week08-potw-suez), [Inball](problems/week06-inball), [Asterix and the Legions](problems/week11-asterix_and_the_legions)                                                                                                                                                                                                                                                                                                                                                    |
| Max-Flow-Min-Cost                                  | [Bonus Level](problems/week12-bonus_level), [Carsharing](/problems/week12-car_sharing), [India](problems/week14-potw-india), [Ludo Bagman](problems/week13-ludo_bagman)                                                                                                                                                                                                                                                                                                                    |
| Maximum Flow                                       | [Majesty's service](problems/week12-majestys_secret_service)                                                                                                                                                                                                                                                                                                                                                                                                                               |
| Maximum Matching                                   | [Majesty's service](problems/week12-majestys_secret_service)                                                                                                                                                                                                                                                                                                                                                                                                                               |
| Minimum Spanning Tree                              | [Clues](problems/week13-potw-clues), [Return of the Jedi](problems/week11-return_of_the_jedi), [Hong Kong](problems/week12-hong_kong), [Idefix](problems/week11-idefix/), [GoldenEye](problems/week10-potw-goldeneye/), [H1N1](problems/week08-h1n1), [Hand](problems/week13-hand)                                                                                                                                                                                                         |
| Prefix Sum                                         | [Even Pairs](problems/week01-even_pairs), [Even Matrices](problems/week01-even_matrices), [The Iron Islands](problems/week11-the_iron_islands), [Deck of Cards](problems/week02-potw-deck_of_cards)                                                                                                                                                                                                                                                                                        |
| Randomization                                      |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            |
| Recursion                                          | [Asterix and the Chariot Race](problems/week10-asterix_and_the_chariot_race), [Hagrid](problems/week13-hagrid)                                                                                                                                                                                                                                                                                                                                                                             |
| Sliding Window                                     | [The Iron Islands](problems/week11-the_iron_islands), [Deck of Cards](problems/week02-potw-deck_of_cards)                                                                                                                                                                                                                                                                                                                                                                                  |
| Sorting                                            | [The Iron Islands](problems/week11-the_iron_islands)                                                                                                                                                                                                                                                                                                                                                                                                                                       |
| Split and List                                     | [Asterix and the Gaul](problems/week05-asterix_the_gaul/)                                                                                                                                                                                                                                                                                                                                                                                                                                  |
| Tree                                               | [Asterix and the Chariot Race](problems/week10-asterix_and_the_chariot_race), [Hagrid](problems/week13-hagrid)                                                                                                                                                                                                                                                                                                                                                                             |
| Union-Find                                         | [Idefix](problems/week11-idefix/), [GoldenEye](problems/week10-potw-goldeneye/), [Hand](problems/week13-hand)                                                                                                                                                                                                                                                                                                                                                                              |