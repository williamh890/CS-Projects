#include <iostream>
#include "include\Matrix.h"

using namespace std;

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

    Matrix<long double>prob30({{1,9,8,0},{6,-6,-12,0},{-5,1,6,0},{1,0,-1,0}});

    Matrix<int> zeroMatrix(3,5);

    vector<double> r1 {2,2,3};
    vector<double> r2 {4,5,7};

    first.scale(0, 2);
    first.print();

    first.interchange(0,1);
    first.print();

    first.replacement(1,0,-.5);
    first.print();

    return 0;
}









