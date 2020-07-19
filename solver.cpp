#include "solver.hpp"
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <unordered_map>
using namespace solver;
using namespace std;


//both
RealVariable solver::operator+(const RealVariable &x, const RealVariable &y)
{
    RealVariable res = x;

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
    RealVariable res = x;

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

RealVariable solver::operator*(const RealVariable &x, const RealVariable &y)
{
    RealVariable res;
    res.umap[1] = 0;
    for (auto it = x.umap.begin(); it != x.umap.end(); it++)
    {
        for (auto it2 = y.umap.begin(); it2 != y.umap.end(); it2++)
        {
            if (it->second != 0 && it2->second != 0)
            {
                double real_number_multi = it->second * it2->second;
                int degree_after_adding = it->first + it2->first;

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
    RealVariable res;
    auto value_at_0 = y.umap.at(0);
    auto value_at_1 = y.umap.at(1);
    auto value_at_2 = y.umap.at(2);
    int new_degree;
    double new_value;
    if ((value_at_0 == 0 && value_at_1 != 0 && value_at_2 == 0) || (value_at_0 == 0 && value_at_1 == 0 && value_at_2 != 0)) // divide only with x
    {
        for (auto it = x.umap.begin(); it != x.umap.end(); it++)
        {
            switch ((int)value_at_1)
            {
            case 0:
                if (it->first < 2) // the degree of x is less than y
                    throw("illegal division!");
                else
                {
                    new_degree = it->first - 2;
                    new_value = it->second / value_at_1;
                    res.umap[new_degree] = new_value;
                }
                break;

            default:

                if (it->first < 1)
                    throw("illegal division!");
                else
                {
                    new_degree = it->first - 1;
                    new_value = it->second / value_at_1;
                    res.umap[new_degree] = new_value;
                }
                break;
            }
        }
    }
    return res;
}

/// left side:
RealVariable solver::operator+(const RealVariable &x, double num)
{
    RealVariable res = x;

    res.umap[0] += num;
    return res;
}

RealVariable solver::operator-(const RealVariable &x, double num)
{

    RealVariable res = x;

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
            res.umap[it->first] = it->second * num;
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
        res.umap[0] = 1;
        break;
    case 1:
        res = x;
        break;
    case 2:
        res = x * x;
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
    RealVariable res = x;

    res.umap[0] += num;
    return res;
}

RealVariable solver::operator-(double num, const RealVariable &x)
{
    RealVariable res = x;

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

    res = x - y;
    return res;
}

double linear_solve(const RealVariable &x)
{
    double result;
    double value_at_0 = x.umap.at(0);
    double value_at_1 = x.umap.at(1);
    result = -(value_at_0 / value_at_1);
    return result;
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
    if (a == 0)
    {
        return linear_solve(e);
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
