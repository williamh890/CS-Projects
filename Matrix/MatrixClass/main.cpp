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

    Matrix<double> A({{1,3,1,5},{5,20,6,31},{-2,-1,-1,-4},{2,10,-0.000042,5002.16}});

    Matrix<double> sqTest({{7,-6,1,6},
                           {2,3,-1,9},
                           {-3,4,-2,-14},
                           {2.5,2,7,1}});

    Matrix<double>prob30({{1,9,8,0},
                          {6,-6,-12,0},
                          {-5,1,6,0},
                          {1,0,-1,0}});

    Matrix<int> zeroMatrix(3,5);

    Matrix<double> result;

    result.print();

    //prob30.subMatrix(std::make_pair(0,0), std::make_pair(1,1));


    rref(second).print();
    rref(prob30).print();
    rref(A).print();

    cout << det(sqTest) << endl;

    return 0;
}









