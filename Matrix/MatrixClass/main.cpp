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

    Matrix<double> sqTest({{4,-7,2},
                           {3,9,-1},
                           {5,5,2}});

    Matrix<double>prob30({{1,9,8,0},
                          {6,-6,-12,0},
                          {-5,1,6,0},
                          {1,0,-1,0}});

    Matrix<int> zeroMatrix(3,5);

    vector<double> r1 {2,2,3};
    vector<double> r2 {4,5,7};

    first.print();
    invert(first).print();

    return 0;
}









