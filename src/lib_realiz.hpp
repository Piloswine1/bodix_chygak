#ifndef LIB_REALIZ_H
#define LIB_REALIZ_H

#include "help_elems.hpp"

namespace VengAlg
{
    /*
     * Рассматриваем матрицу:
     * (0,1)  ... (0,N)
     * .            .
     * .            .
     * .            .
     * (N-1,1)... (N-1,N)
     */
    template<unsigned long N>
    Matrix<N> delete_min_row(const Matrix<N> &mat)
    {
        Matrix<N> retval(mat);
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

    template<unsigned long N>
    Matrix<N> delete_min_col(const Matrix<N> &mat)
    {
        Matrix<N> retval(mat);
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
    template<unsigned long N>
    ListOfElems try_row_optimal(const Matrix<N> &mat)
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
    template<unsigned long N>
    ListOfElems try_col_optimal(const Matrix<N> &mat)
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

    template<unsigned long N>
    bool isOptimal(const ListOfElems &elems)
    {
        return elems.size() < N-1;
    }

    template<unsigned long N>
    Matrix<N> to_optimal(const Matrix<N> &mat)
    {
        //TODO: implement fix
        return Matrix<N>{0};
    }

    elemPos findElem(const int &i, const ListOfElems &elems)
    {
        for (auto it = elems.begin(); it != elems.end(); ++it)
            if (i == it->i) return *it;
        return elemPos{-1,-1,-1};
    }

    template<unsigned long N>
    SubPathList make_subpathes(const ListOfElems &elems)
    {
        SubPathList retval;
        ListOfElems removed;
        for (int i = 0; i < N-1; ++i) {
            elemPos elem = findElem(i, elems);

            if (elem.i == -1) {
                std::cout<<"elem not found:\n";
                std::cout<<elem;
                continue;
            }
            if (isRemoved(elem, removed))
                continue;

            Dlist subpath;
            const int first = elem.i;
            int next = elem.j;
            for (; next != first                &&
                   !isRemoved(elem, removed)    &&
                   elem.i != -1;
                 next = elem.j)
            {
                subpath.push_back(D{elem.i, elem.val});
                removed.push_back(elem);
                elem = findElem(next, elems);
            }
            retval.push_back(subpath);
        }
        return retval;
    }

    template<unsigned long N>
    SubPathList solve_destination(const Matrix<N> &mat)
    {
        // шаг 1
        const Matrix<N> row = delete_min_row(mat);
        const Matrix<N> col = delete_min_col(mat);

        // шаг 2
        const ListOfElems row_e = try_row_optimal(row);
        const ListOfElems col_e = try_col_optimal(col);

        // если по строкам оптимальней
        if (isOptimal<N>(row_e))
            return make_subpathes<N>(row_e);

        // если по столбцам оптимальней
        if (isOptimal<N>(col_e))
            return make_subpathes<N>(col_e);

        // шаг 3
//        const Matrix<N> ret{};
        const ListOfElems ret_elems{};
        return make_subpathes<N>(ret_elems);
    }
}

namespace Util {
    template<unsigned long N>
    Matrix<N> make_upper_triangle(const Matrix<N> &mat)
    {
        Matrix<N> retval{0};
        for (int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                if (i > j)
                    retval[i][j] = mat[i][j];
        return retval;
    }
}

//int main()
//{
//    Matrix<N> arr = {
//        0,6,10,6,4,0,8,0,0,6,
//        //TODO: заполнить далее
//    };

//    Matrix<N> triangle = Util::make_upper_triangle(arr);
//    SubPathList destination = solve_destination(triangle);
//    Dlist list = Salesman::solve_path(destination);
//    printDest(list);

//	return 0;
//}

#endif // LIB_REALIZ_H
