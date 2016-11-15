#include <iostream>
#include "include\Matrix.h"

using namespace std;

vector<int> name;

int main()
{
    Matrix<double>  first({{1,2,3},
                           {4,5,6}});

    Matrix<double> second({{1, 2, 4, 8},
                           { 2, 4, 6, 8},
                           {3, 6, 9, 13}});

    Matrix<int> zeroMatrix(3,5);

    vector<double> r1 {2,2,3};
    vector<double> r2 {4,5,7};

    second.print();
    rref(second).print();

    return 0;
}
