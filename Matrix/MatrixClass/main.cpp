#include <iostream>
#include "include\Matrix.h"

using namespace std;

vector<int> name;

int main()
{
    Matrix<double>  first({{1,2,3},
                           {4,5,6}});

    Matrix<double> second({{3,-9,12,-9,6,15},
                           {3,-7,8,-5,8,9},
                           {0,3,-6,6,4,-5}});
    Matrix<double> result(2,2);

    ref(second);

    return 0;
}
