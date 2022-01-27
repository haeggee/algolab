///
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Gmpq.h>
#include <tuple>
#include <algorithm>

// choose input type (input coefficients must fit)
typedef CGAL::Gmpq IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
// points with index
struct Point
{
    int x;
    int y;
    int ind;
};

double floor_to_double(const CGAL::Quotient<ET> &x)
{
    double a = std::floor(CGAL::to_double(x));
    while (a > x)
        a -= 1;
    while (a + 1 <= x)
        a += 1;
    return a;
}

void testcase()
{

    // set the coefficients of A and b
    int n, m, h, w;
    std::cin >> n >> m >> h >> w;

    Program lp(CGAL::SMALLER, true, 1, false, 0);
    std::vector<Point> n_pts(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        std::cin >> x >> y;
        n_pts[i] = {x, y, i};
        lp.set_c(i, -2 * (h + w));
    }
    std::vector<Point> m_pts(m);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        std::cin >> x >> y;
        m_pts[i] = {x, y, i};
    }

    int n_constr = n;
    
    // constraints between new posters
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int diff_x = std::abs(n_pts[i].x - n_pts[j].x);
            int diff_y = std::abs(n_pts[i].y - n_pts[j].y);
            // either they would first hit horizontally or vertically
            ET b = std::max(ET(2 * diff_x, w), ET(2 * diff_y, h));
            lp.set_a(i, n_constr, 1);
            lp.set_a(j, n_constr, 1);
            lp.set_b(n_constr, b);
            n_constr++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        ET min_constr = ET(std::numeric_limits<double>::max());
        for (int j = 0; j < m; j++)
        {
            int diff_x = std::abs(n_pts[i].x - m_pts[j].x);
            int diff_y = std::abs(n_pts[i].y - m_pts[j].y);
            // either they would first hit horizontally or vertically
            ET b = std::max(ET(2 * diff_x, w) - 1, ET(2 * diff_y, h) - 1);
            min_constr = std::min(min_constr, b);
        }
        lp.set_a(i, n_constr, 1);
        lp.set_b(n_constr, min_constr);
        n_constr++;
    }

    
    Solution s = CGAL::solve_linear_program(lp, ET());
    // std::cerr << s << std::endl;
    if (s.is_unbounded()) // just a sanity check
    {
        std::cout << "unbounded" << std::endl;
    }
    else
    {
        auto val = s.objective_value();
        // cerr << s << std::endl;
        std::cout << long(-floor_to_double(val)) << std::endl;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false); // Always!
    int t;
    std::cin >> t;
    while (t--)
        testcase();
}
