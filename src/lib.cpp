#include "lib.hpp"

namespace Salesman
{

    SubPathList remove_unness(const SubPathList &list)
    {
        SubPathList retval(list);
        for (auto &subpath: retval)
            for (auto it = std::next(subpath.begin()); it != subpath.end();)
                if (it->cost == 0)
                    it = subpath.erase(it);
                else
                    ++it;
        return retval;
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

    Dlist solve_path(const SubPathList &list)
    {
        return to_path(remove_unness(list));
    }
}


void printDest(const Dlist &list)
{
    std::cout<<list.front().v;
    for (auto it = std::next(list.begin()); it != list.end(); ++it)
        std::cout<<", "<<it->v;
    std::cout<<'\n';
}
