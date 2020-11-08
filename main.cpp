#include <iostream>
#include <algorithm>
#include <array>
#include <list>

struct D
{
    int v, cost;
};

const int N = 10;

typedef std::array<std::array<int, N>, N> Matrix;
typedef std::list<D> Dlist;
typedef std::list<Dlist> SubPathList;

namespace VengAlg
{
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

    /*
     * Рассматриваем матрицу:
     * (0,1)  ... (0,N)
     * .            .
     * .            .
     * .            .
     * (N-1,1)... (N-1,N)
     */

    Matrix delete_min_row(const Matrix &mat)
    {
        Matrix retval(mat);
        // идем по строкам
        for (int i = 0; i < N-1; ++i)
        {
            int min = retval[i][1];
            // 2..N ищем минимальный элемент
            for (int j = 2; j < N; ++j)
                min = std::min(min, retval[i][j]);
            // удаляем его
            for (int j = 1; j < N; ++j)
                retval[i][j] -= min;
        }
        return retval;
    }

    Matrix delete_min_col(const Matrix &mat)
    {
        Matrix retval(mat);
        // идем по столбцам
        for (int j = 1; j < N; ++j)
        {
            int min = retval[0][j];
            // 1..N-1 ищем минимальный элемент
            for (int i = 1; i < N-1; ++i)
                min = std::min(min, retval[i][j]);
            // удаляем его
            for (int i = 0; i < N-1; ++i)
                retval[i][j] -= min;
        }
        return retval;
    }

    bool isRemoved(const elemPos &elem, const ListOfElems &list)
    {
        for (auto it = list.begin(); it != list.end(); ++it)
            if (elem == *it) return true;
        return false;
    }

    // смотрим строки
    ListOfElems try_row_optimal(const Matrix &mat)
    {
        ListOfElems retval, removed;
        for (int i = 0; i < N-1; ++i) {
            int zeros = 0;
            elemPos elem;
            for (int j = 1; j < N; ++j) {
                elem = {i, j, mat[i][j]};
                // если элемент = 0 и не вычеркнут считаем
                if (elem.val == 0 && !isRemoved(elem, removed))
                    zeros++;
            }
            // если один ноль в строке - назначем елемент
            // и вычеркиваем нули из столбцов
            if (zeros == 1) {
                retval.push_back(elem);
                for (int j = 1; j < N-1; ++j) {
                    const elemPos _elem{elem.i, j, mat[elem.i][j]};
                    // если элемент = 0 и не вычеркнут считаем
                    if (_elem.val == 0 && !isRemoved(_elem, removed))
                        removed.push_back(_elem);
                }
            }
        }
        return retval;
    }

    // смотрим столбцы
    ListOfElems try_col_optimal(const Matrix &mat)
    {
        ListOfElems retval, removed;
        for (int j = 1; j < N; ++j) {
            int zeros = 0;
            elemPos elem;
            for (int i = 0; i < N-1; ++i) {
                elem = {i, j, mat[i][j]};
                // если элемент = 0 и не вычеркнут считаем
                if (elem.val == 0 && !isRemoved(elem, removed))
                    zeros++;
            }
            // если один ноль в столбце - назначем елемент
            // и вычеркиваем нули из строки
            if (zeros == 1) {
                retval.push_back(elem);
                for (int i = 0; i < N; ++i) {
                    const elemPos _elem{i, elem.j, mat[i][elem.j]};
                    // если элемент = 0 и не вычеркнут считаем
                    if (_elem.val == 0 && !isRemoved(_elem, removed))
                        removed.push_back(_elem);
                }
            }
        }
        return retval;
    }

    bool isOptimal(const Matrix &mat, const ListOfElems &elems)
    {
        RList rlist;
        for (int i = 0; i < N-1; ++i)
            for (int j = 1; j < N; ++j)
                if (mat[i][j] == 0) {
                    R r{
                        .from = i,
                        .to = j
                    };
                    rlist.push_back(r);
                }

        return false;
    }

    Matrix to_optimal(const Matrix &mat)
    {
        //TODO: implement fix
        return Matrix{0};
    }

    SubPathList make_subpathes(const Matrix &mat, const ListOfElems &elems)
    {
        SubPathList retval;

        return retval;
    }

    SubPathList solve_destination(const Matrix &mat)
    {
        // шаг 1
        const Matrix row = delete_min_row(mat);
        const Matrix col = delete_min_col(mat);

        // шаг 2
        const ListOfElems row_e = try_row_optimal(row);
        const ListOfElems col_e = try_col_optimal(col);

        // если по строкам оптимальней
        if (isOptimal(row, row_e))
            return make_subpathes(row, row_e);

        // если по столбцам оптимальней
        if (isOptimal(col, col_e))
            return make_subpathes(col, col_e);

        // шаг 3
        const Matrix ret{};
        const ListOfElems ret_elems{};
        return make_subpathes(ret, ret_elems);
    }
}

namespace Salesman
{

    void remove_unness(SubPathList &list)
    {
        for (auto &subpath: list)
            for (auto it = std::next(subpath.begin()); it != subpath.end();)
                if (it->cost == 0)
                    subpath.erase(it);
                else
                    ++it;
    }

    Dlist to_path(const SubPathList &list)
    {
        Dlist retval(list.front());
        // идем с конца до 2-го элемента
        for (auto it = list.rbegin(); it != std::prev(list.rend()); ++it)
            // для каждой вершины, добавляем ее в путь
            for (auto _it = it->begin(); _it != it->end(); ++_it)
                retval.push_back(*_it);
        return retval;
    }

    Dlist solve_path(SubPathList &list)
    {
        remove_unness(list);
        return to_path(list);
    }
}

namespace Util
{
    Matrix make_upper_triangle(const Matrix &mat)
    {
        Matrix retval{0};
        for (int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                if (i > j)
                    retval[i][j] = mat[i][j];
        return retval;
    }

}

void printDest(const Dlist &list)
{
    std::cout<<list.front().v;
    for (auto it = std::next(list.begin()); it != list.end(); ++it)
        std::cout<<", "<<it->v;
    std::cout<<'\n';
}

int main()
{
    Matrix arr = {
        0,6,10,6,4,0,8,0,0,6,
        //TODO: заполнить далее
    };

    Matrix triangle = Util::make_upper_triangle(arr);
    SubPathList destination = VengAlg::solve_destination(triangle);
    Dlist list = Salesman::solve_path(destination);
    printDest(list);

	return 0;
}
