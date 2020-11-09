#ifndef HELP_ELEMS_HPP
#define HELP_ELEMS_HPP

#include <iostream>
#include <algorithm>
#include <array>
#include <list>

template<unsigned long N>
struct Matrix
{
    std::array<std::array<int, N>, N> _arr;
    std::array<int, N>& operator[](const int &i)
    {
        if (i > N-1)
            throw std::out_of_range("failed to move out");
        return _arr[i];
    }
    const std::array<int, N>& operator[](const int &i) const
    {
        if (i > N-1)
            throw std::out_of_range("failed to move out");
        return _arr[i];
    }
    bool operator==(const Matrix<N> &m)
    {
        return _arr == m._arr;
    }
};

struct elemPos
{
    int i, j, val;
    bool operator==(const elemPos &e) const
    {
        return (i == e.i && j == e.j);
    }
};


struct R
{
    int from, to;
};

typedef std::list<R> RList;
typedef std::list<int> ListNulled;
typedef std::list<elemPos> ListOfElems;


struct D
{
    int v, cost;
    bool operator==(const D &d) const
    {
        return v == d.v && cost == d.cost;
    }
};

typedef std::list<D> Dlist;
typedef std::list<Dlist> SubPathList;


std::ostream&  operator<<(std::ostream &o, const D &d)
{
    return o<<"{v:\t"<<d.v<<",\tcost:\t"<<d.cost<<'}';
}

std::ostream&  operator<<(std::ostream &o, const Dlist &list)
{
    o<<'\n'<<list.front();
    std::for_each(std::next(list.begin()), std::prev(list.end()), [&](const auto &e) {
        o<<",\t"<<e;
    });
    return o<<'\n';
}

#endif // HELP_ELEMS_HPP
