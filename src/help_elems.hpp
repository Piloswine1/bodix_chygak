#ifndef HELP_ELEMS_HPP
#define HELP_ELEMS_HPP

#include <iostream>
#include <algorithm>
#include <array>
#include <list>

template<unsigned long N>
struct Matrix
{
    typedef std::array<std::array<int, N>, N> _matrix;
    Matrix(const _matrix &__arr):
        _arr(__arr)
    {}
    template<typename ...T>
    constexpr Matrix(const T &..._list):
        _arr({_list...})
    {
        static_assert (sizeof... (_list) == N*N);
    }
    Matrix transpose() const
    {
        _matrix temp{0};
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                temp[N-1-j][N-1-i] = _arr[i][j];
        return Matrix(temp);
    }
    std::array<int, N>& operator[](const int &i)
    {
        return _arr[i];
    }
    const std::array<int, N>& operator[](const int &i) const
    {
        return _arr[i];
    }
    bool operator==(const Matrix<N> &m)
    {
        return _arr == m._arr;
    }
    friend std::ostream&  operator<<(std::ostream &o, const Matrix<N> &mat)
    {
        o<<"[\n";
        for (const auto &e: mat._arr)
            o<<'\t'<<e<<'\n';
        return o<<"\t]";
    }
private:
    _matrix _arr;
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

std::ostream&  operator<<(std::ostream &o, const elemPos &e)
{
    return o<<"{\ti: "<<e.i<<",\n\tj: "<<e.j<<",\n\tval: "<<e.val<<"\n}\n";
}

template<unsigned long N>
std::ostream&  operator<<(std::ostream &o, const std::array<int, N> &a)
{
    o<<a[0];
    for(int i = 1; i < N; ++i)
        o<<",\t"<<a[i];
    return o;
}

#endif // HELP_ELEMS_HPP
