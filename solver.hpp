#include <iostream>
#include <unordered_map>
using namespace std;

namespace solver
{

    class RealVariable
    {
    public:
        unordered_map<int, double> umap = {{0, 0},
                                           {1, 0},
                                           {2, 0}};

        //right
        friend RealVariable operator-(const double num, const RealVariable &x);
        friend RealVariable operator/(const double num, const RealVariable &x);
        friend RealVariable operator+(const double num, const RealVariable &x);
        friend RealVariable operator*(const double num, const RealVariable &x);
        friend RealVariable operator^(const double num, const RealVariable &x);

        //left
        friend RealVariable operator+(const RealVariable &x, const double num);
        friend RealVariable operator-(const RealVariable &x, const double num);
        friend RealVariable operator*(const RealVariable &x, const double num);
        friend RealVariable operator/(const RealVariable &x, const double num);
        friend RealVariable operator^(const RealVariable &x, const int num);

        //both
        friend RealVariable operator+(const RealVariable &x1, const RealVariable &x);
        friend RealVariable operator-(const RealVariable &x1, const RealVariable &x);
        friend RealVariable operator*(const RealVariable &x1, const RealVariable &x);
        friend RealVariable operator/(const RealVariable &x1, const RealVariable &x);
        // friend RealVariable operator^(const RealVariable &x1, const RealVariable &x);
        //relevant for solve function
        friend RealVariable operator==(const double num, const RealVariable &x);
        friend RealVariable operator==(const RealVariable &x, const double num);
        friend RealVariable operator==(const RealVariable &x1, const RealVariable &x)
        {
        }
    };

}; // namespace solver
