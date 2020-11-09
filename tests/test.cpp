#include "ut.hpp"
#include "src/lib.hpp"

using namespace boost::ut;

suite deletes = [] {
    typedef Matrix<5> testMatr;

    "delete row"_test = [] {
        const testMatr in {
            0,  2,  10, 9,  7,
            0,  15, 4,  14, 8,
            0,  13, 14, 16, 11,
            0,  4,  15, 13, 19,
            0,  0,  0,  0,  0
        };
        const testMatr exp {
            0,	0,	8,	7,	5,
            0,	11,	0,	10,	4,
            0,	2,	3,	5,	0,
            0,	0,	11,	9,	15,
            0,	0,	0,	0,	0
        };
        const testMatr ret = VengAlg::delete_min_row(in);
        expect(eq(ret, exp))<<"\n\twith in:\n"<<in<<'\n';
    };
    "delete col"_test = [] {
        const testMatr in {
            0,  2,  10, 9,  7,
            0,  15, 4,  14, 8,
            0,  13, 14, 16, 11,
            0,  4,  15, 13, 19,
            0,  0,  0,  0,  0
        };
        const testMatr exp {
            0,	0,	6,	0,	0,
            0,	13,	0,	5,	1,
            0,	11,	10,	7,	4,
            0,	2,	11,	4,	12,
            0,	0,	0,	0,	0,
        };
        const testMatr ret = VengAlg::delete_min_col(in);
        expect(eq(ret, exp))<<"\n\twith in:\n"<<in<<'\n';
    };
    "delete all"_test = [] {
        const testMatr in {
            0,  2,  10, 9,  7,
            0,  15, 4,  14, 8,
            0,  13, 14, 16, 11,
            0,  4,  15, 13, 19,
            0,  0,  0,  0,  0
        };
        const testMatr exp {
            0,	0,	6,	0,	0,
            0,	13,	0,	5,	1,
            0,	7,	6,	3,	0,
            0,	0,	9,	2,	10,
            0,	0,	0,	0,	0
        };
        const testMatr ret = VengAlg::delete_min_row(
                    VengAlg::delete_min_col(in)
        );
        expect(eq(ret, exp))<<"\n\twith in:\n"<<in<<'\n';
    };

};

suite paths = [] {
    "remove unneccesary"_test = [] {
        const SubPathList in = {
            Dlist{D{1, 0},D{4, -20},D{3, 1},D{7, 2}},
            Dlist{D{2, 0},D{2, 0}},
            Dlist{D{5, 0},D{6, -18},D{5, 0}}
        };
        const SubPathList exp = {
            Dlist{D{1, 0},D{4, -20},D{3, 1},D{7, 2}},
            Dlist{D{2, 0}},
            Dlist{D{5, 0},D{6, -18}}
        };
        const SubPathList ret = Salesman::remove_unness(in);
        expect(eq(ret, exp))<<"\n\twith in:\n"<<in<<'\n';
    };

    "to path"_test = [] {
        const SubPathList in = {
            Dlist{D{1, 0},D{4, -20},D{3, 1},D{7, 2}},
            Dlist{D{2, 0}},
            Dlist{D{5, 0},D{6, -18}}
        };
        const Dlist exp = {
            D{1, 0},
            D{4, -20},
            D{3, 1},
            D{7, 2},
            D{5, 0},
            D{6, -18},
            D{2, 0}
        };
        const Dlist ret = Salesman::to_path(in);
        expect(eq(ret, exp))<<"\n\twith in:\n"<<in<<'\n';
    };

    "complex path"_test = [] {
        const SubPathList in = {
            Dlist{D{1, 0},D{4, -20},D{3, 1},D{7, 2}},
            Dlist{D{2, 0},D{2, 0}},
            Dlist{D{5, 0},D{6, -18},D{5, 0}}
        };
        const Dlist exp = {
            D{1, 0},
            D{4, -20},
            D{3, 1},
            D{7, 2},
            D{5, 0},
            D{6, -18},
            D{2, 0}
        };
        const Dlist ret = Salesman::solve_path(in);
        expect(eq(ret, exp))<<"\n\twith in:\n"<<in<<'\n';
    };
};

int main() {

}
