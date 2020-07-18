#include "solver.hpp"

using namespace solver;
using namespace std;

//both
solver::RealVariable operator+(const RealVariable &x, const RealVariable &y)
{
    RealVariable res;

    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        cout << it->first << "  " << it->second << endl;
        if (it->second != 0) // if there is a real number
        {
            res.umap[it->first] += it->second; // add to res.umap[degree] value of x in the same degree
        }
    }

    for (auto it2 = y.umap.begin(); it2 != y.umap.end(); it2++)
    {
        cout << it2->first << "  " << it2->second << endl;
        if (it2->second != 0) // if there is a real number
        {
            res.umap[it2->first] += it2->second; // add to res.umap[degree] value of x in the same degree
        }
    }
    return res;
}

solver::RealVariable operator-(const RealVariable &x, const RealVariable &y)
{
    RealVariable res;

    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        cout << it->first << "  " << it->second << endl;
        if (it->second != 0) // if there is a real number
        {
            res.umap[it->first] += it->second; // add to res.umap[degree] value of x in the same degree
        }
    }

    for (auto it2 = y.umap.begin(); it2 != y.umap.end(); it2++)
    {
        cout << it2->first << "  " << it2->second << endl;
        if (it2->second != 0) // if there is a real number
        {
            res.umap[it2->first] -= it2->second; // add to res.umap[degree] value of x in the same degree
        }
    }
    return res;
}

solver::RealVariable operator*(const RealVariable &x, const RealVariable &y)
{
    RealVariable res;
    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        for (auto it2 = y.umap.begin(); it2 != y.umap.end(); it2++)
        {
            double real_number_multi = it->second * it2->second;
            int degree_after_adding = it->first + it2->first;
            if (real_number_multi != 0)
            {

                switch (degree_after_adding)
                {
                case 0:
                    res.umap[0] += real_number_multi;
                    break;
                case 1:
                    res.umap[1] += real_number_multi;
                    break;
                case 2:
                {
                    res.umap[2] += real_number_multi;
                    break;
                }
                default:
                    throw("Degree is not allowed!");
                    break;
                }
            }
        }
    }
    return res;
}


solver::RealVariable operator/(const RealVariable &x, const RealVariable &y){
    return x;
}





