#include "solver.hpp"
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <unordered_map>
using namespace solver;
using namespace std;

// ostream &solver::operator<<(ostream &out, const solver::RealVariable &var)
// {
//     for (auto it = var.umap.begin(); it != var.umap.end(); it++)
//     {

//         out << it->second;
//         if (it->first > 0)
//         {
//             out << "x^" << it->first;
//         }

//         out << " ";
//     }
//     return out;
// }

//both
RealVariable solver::operator+(const RealVariable &x, const RealVariable &y)
{
    RealVariable res;

    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        // cout << it->first << "  " << it->second << endl;
        if (it->second != 0) // if there is a real number
        {
            res.umap[it->first] += it->second; // add to res.umap[degree] value of x in the same degree
        }
    }

    for (auto it2 = y.umap.begin(); it2 != y.umap.end(); it2++)
    {
        // cout << it2->first << "  " << it2->second << endl;
        if (it2->second != 0) // if there is a real number
        {
            res.umap[it2->first] += it2->second; // add to res.umap[degree] value of x in the same degree
        }
    }
    return res;
}

RealVariable solver::operator-(const RealVariable &x, const RealVariable &y)
{
    RealVariable res;

    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        // cout << it->first << "  " << it->second << endl;
        if (it->second != 0) // if there is a real number
        {
            res.umap[it->first] += it->second; // add to res.umap[degree] value of x in the same degree
        }
    }

    for (auto it2 = y.umap.begin(); it2 != y.umap.end(); it2++)
    {
        // cout << it2->first << "  " << it2->second << endl;
        if (it2->second != 0) // if there is a real number
        {
            res.umap[it2->first] -= it2->second; // add to res.umap[degree] value of x in the same degree
        }
    }
    return res;
}

RealVariable operator*(const RealVariable &x, const RealVariable &y)
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

RealVariable solver::operator/(const RealVariable &x, const RealVariable &y)
{
    return x;
}

/// left side:
RealVariable solver::operator+(const RealVariable &x, double num)
{
    RealVariable res;

    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        if (it->second != 0) // if there is a real number
        {
            res.umap[it->first] += it->second; // add to res.umap[degree] value of x in the same degree
        }
    }

    res.umap[0] += num;
    return res;
}

RealVariable solver::operator-(const RealVariable &x, double num)
{

    RealVariable res;

    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        if (it->second != 0) // if there is a real number
        {
            res.umap[it->first] = it->second; // add to res.umap[degree] value of x in the same degree
        }
    }

    res.umap[0] -= num;
    return res;
}

RealVariable solver::operator*(const RealVariable &x, double num)
{
    RealVariable res;
    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        if (it->second != 0)
        {
            res.umap[it->first] += it->second * num;
        }
    }
    return res;
}

RealVariable solver::operator/(const RealVariable &x, double num)
{
    RealVariable res;
    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        if (it->second != 0)
        {
            res.umap[it->first] = it->second / num;
        }
    }
    return res;
}

RealVariable solver::operator^(const RealVariable &x, const double num)
{
    RealVariable res;
    switch ((int)num)
    {
    case 0:
        res.umap[0] += 1;
        break;
    case 1:
        res = x;
        break;
    case 2:
    {
        for (auto it = x.umap.begin(); it != x.umap.end(); it++)
        {
            for (auto it2 = x.umap.begin(); it2 != x.umap.end(); it2++)
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
    }
    // res = x * x;
    break;
    default:
        throw("illegal degree!");
        break;
    }
    return res;
}

// right side:

RealVariable solver::operator+(double num, const RealVariable &x)
{
    RealVariable res;

    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        if (it->second != 0) // if there is a real number
        {
            res.umap[it->first] += it->second; // add to res.umap[degree] value of x in the same degree
        }
    }

    res.umap[0] += num;
    return res;
}

RealVariable solver::operator-(double num, const RealVariable &x)
{
    RealVariable res;

    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        if (it->second != 0) // if there is a real number
        {
            res.umap[it->first] += it->second; // add to res.umap[degree] value of x in the same degree
        }
    }

    res.umap[0] -= num;
    return res;
}
RealVariable solver::operator*(double num, const RealVariable &x)
{
    RealVariable res;
    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        if (it->second != 0)
        {
            res.umap[it->first] = (it->second * num);
        }
    }
    return res;
}
// Equation
RealVariable solver::operator==(double num, const RealVariable &x)
{

    RealVariable res;
    res = x;
    res.umap[0] -= num;
    return res;
}
RealVariable solver::operator==(const RealVariable &x, double num)
{
    RealVariable res;
    res = x;
    res.umap[0] -= num;
    return res;
}
RealVariable solver::operator==(const RealVariable &x, const RealVariable &y)
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

    // RealVariable res = x - y;
    // return res;
}

double solver::solve(const RealVariable &e)
{
    double a, b, c = 0;
    float x1, x2, discriminant, realPart, imaginaryPart;
    for (auto it = e.umap.begin(); it != e.umap.end(); it++)

        switch (it->first)
        {
        case 0:

            c = it->second;
            cout << "c = " << c << endl;

            break;
        case 1:
            b = it->second;
            cout << "b = " << b << endl;

            break;
        case 2:
            a = it->second;
            cout << "a = " << a << endl;

            break;
        }

    discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        x1 = (-b + sqrt(discriminant)) / (2 * a);
        x2 = (-b - sqrt(discriminant)) / (2 * a);
        cout << "Roots are real and different." << endl;
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }

    else if (discriminant == 0)
    {
        cout << "Roots are real and same." << endl;
        x1 = (-b + sqrt(discriminant)) / (2 * a);
        cout << "x1 = x2 =" << x1 << endl;
    }
    else
    {
        throw("There is no real solution!");
    }
    return x1;
}
