#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase() {

    long xs, ys, n;
    std::cin >> xs >> ys >> n;
    // create an LP with Ax <= b and no lower/upper bounds
    Program lp (CGAL::SMALLER, false, 0, false, 0); 
    const int x = 0;
    const int y = 1;
    const int r = 2;

    for(int i = 0; i < n; i++) {
        long a, b, c, v;
        std::cin >> a >> b >> c >> v;
        long len = std::sqrt(a * a + b * b);
        // set up constraint a x + b y + c <= 0
        if(a * xs + b * ys + c < 0) {
            lp.set_a(x, i, a); 
            lp.set_a(y, i, b);
            lp.set_a(r, i, len * v);
            lp.set_b(i, -c);
        } else { // flip signs
            lp.set_a(x, i, -a); 
            lp.set_a(y, i, -b);
            lp.set_a(r, i, len * v);
            lp.set_b(i, c);
        }
    }

    // enforce that r is positive
    lp.set_l(r, true, 0);
    // maximize
    lp.set_c(r, -1);
    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    assert(s.solves_linear_program(lp));
    
    // output solution
    std::cout << -s.objective_value().numerator() / s.objective_value().denominator() << std::endl; 
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
