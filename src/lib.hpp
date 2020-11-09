#ifndef LIB_H
#define LIB_H

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
    Matrix<N> delete_min_row(const Matrix<N> &mat);
    template<unsigned long N>
    Matrix<N> delete_min_col(const Matrix<N> &mat);
    bool isRemoved(const elemPos &elem, const ListOfElems &list);
    // смотрим строки
    template<unsigned long N>
    ListOfElems try_row_optimal(const Matrix<N> &mat);
    // смотрим столбцы
    template<unsigned long N>
    ListOfElems try_col_optimal(const Matrix<N> &mat);
    template<unsigned long N>
    bool isOptimal(const ListOfElems &elems);
    template<unsigned long N>
    Matrix<N> to_optimal(const Matrix<N> &mat);
    elemPos findElem(const int &i, const ListOfElems &elems);
    template<unsigned long N>
    SubPathList make_subpathes(const ListOfElems &elems);
    template<unsigned long N>
    SubPathList solve_destination(const Matrix<N> &mat);
}

namespace Salesman
{
    SubPathList remove_unness(const SubPathList &list);
    Dlist to_path(const SubPathList &list);
    Dlist solve_path(const SubPathList &list);
}

namespace Util
{
    template<unsigned long N>
    Matrix<N> make_upper_triangle(const Matrix<N> &mat);
}

#include "lib_realiz.hpp"

#endif // LIB_H
