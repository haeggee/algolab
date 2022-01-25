Tags: Linear Programming, Linear Separation

Key ideas:
* Linear Program with variables x, y, r
* Objective: maximize r
* Constraints:
  * We have initial point p_x, p_y
  * For each line with a * x + b * y + c = 0, to stay on the same side:
    * if a * p_x + b * p_y + c < 0, we need conversely need a * x + b * y <= -c
    * if a * p_x + b * p_y + c > 0, we need conversely need -a * x - b * y <= c
  * cf [Inball](../week6-inball) (or the hints given) that we have the distance to the line:
    * (a * x + b * y + c / sqrt(a^2+b^2))
  * To also consider the speed v of the legion, we additionally multiply r by v in the constraint
  * This gives the actual constraint +-a * x +- b * y + sqrt(a^2+b^2) * v * r <>= +- c
* As usual, solve, read out solution (which is guaranteed to exist here)
* IT int suffices, but the computations with a, b, and the sqrt need double or long