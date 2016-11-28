#include <iostream>
#include "include\Matrix.h"

using namespace std;

int main()
{
    Matrix<double> first({{1,2},
                          {4,5}});

    Matrix<double> second({{1, 2, 4, 8},
                           { 2, 4, 6, 8},
                           {3, 6, 9, 13}});

    Matrix<double> A({{-2.6,3,-6,6},
                      {3,-9,22.5,-9},
                      {3,-7,-8,-5},
                      {0,0,0,0}});

    Matrix<double> sqTest({{7,0,1},
                           {0,3,-1},
                           {-3,4,-2}});

    Matrix<double>prob30({{1,9,8,0},
                          {6,-6,-12,0},
                          {-5,1,6,0},
                          {1,0,-1,0}});

    Matrix<int> zeroMatrix(3,5);

    cout << det(sqTest) << endl;

//    rref(second).print();
//    rref(prob30).print();
//    rref(A).print();

    return 0;
}









