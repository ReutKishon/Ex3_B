#include <iostream>
#include <unordered_map>
using namespace std;

namespace solver
{

    class RealVariable
    {
        public:
        unordered_map<int, double> umap;
        friend RealVariable operator+(const RealVariable &x, const RealVariable &y);
    };

} // namespace solver