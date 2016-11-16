#include <iostream>
#include "include\Matrix.h"

using namespace std;

vector<int> name;

int main()
{
    Matrix<double> first({{1,2,3},
                           {4,5,6}});

    Matrix<double> second({{1, 2, 4, 8},
                           { 2, 4, 6, 8},
                           {3, 6, 9, 13}});

    Matrix<double> rrefTest({{3,-9,12,-9,6,15},{3,-7,8,-5,8,9},{0,3,-6,6,4,-5}});

    Matrix<double> sqTest({{4,-7,2},
                           {3,9,-1},
                           {5,5,2}});

    Matrix<int> zeroMatrix(3,5);

    vector<double> r1 {2,2,3};
    vector<double> r2 {4,5,7};

    rref(second).print();
    rref(transpose(first)).print();
    rref(rrefTest).print();
    rref(sqTest).print();
    //rref(zeroMatrix).print();

    return 0;
}









