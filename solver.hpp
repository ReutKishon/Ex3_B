#ifndef SOLVER_A_MASTER_SOLVER_HPP
#define SOLVER_A_MASTER_SOLVER_HPP
#include <iostream>
#include <unordered_map>
using namespace std;

namespace solver
{

    class RealVariable
    {
    public:
        unordered_map<int, double> umap;
        RealVariable()

        {
            umap = {{0, 0},
                    {1, 1},
                    {2, 0}};
        }
    };

    //right
    // friend ostream &operator<<(ostream &out, const RealVariable &var);

    RealVariable operator-(double num, const RealVariable &x);
    RealVariable operator+(double num, const RealVariable &x);
    RealVariable operator*(double num, const RealVariable &x);
    //left
    RealVariable operator+(const RealVariable &x, double num);
    RealVariable operator-(const RealVariable &x, double num);
    RealVariable operator*(const RealVariable &x, double num);
    RealVariable operator/(const RealVariable &x, double num);
    RealVariable operator^(const RealVariable &x, const double num);

    //both
    RealVariable operator+(const RealVariable &x1, const RealVariable &x);
    RealVariable operator-(const RealVariable &x1, const RealVariable &x);
    RealVariable operator*(const RealVariable &x, const RealVariable &y);
    RealVariable operator/(const RealVariable &x1, const RealVariable &x);
    // friend RealVariable operator^(const RealVariable &x1, const RealVariable &x);
    //relevant for solve function
    RealVariable operator==(double num, const RealVariable &x);
    RealVariable operator==(const RealVariable &x, double num);
    RealVariable operator==(const RealVariable &x1, const RealVariable &x);
    double solve(const RealVariable &e);

}; // namespace solver
#endif
