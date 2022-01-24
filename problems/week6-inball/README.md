Tags: Linear Programming, Geometry

Key ideas:
* distance between point and a line in d-dimensions is r = (a^T * x  - b)/norm(a) for a line that is given by the linear constraints a^T * x = b. See, for instance, that the equality holds when r = 0.
* Since we have exactly this form here of a^T * x <= b , we can set the look for the center of the circle while maximizing the radius r, which gives the constraints:
  * a^T * x + r * norm(a) <= b