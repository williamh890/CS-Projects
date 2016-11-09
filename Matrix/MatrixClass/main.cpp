#include <iostream>
#include "include\Matrix.h"

using namespace std;

vector<int> name;

int main()
{
    Matrix<double>  first({{1,2,3},{4,5,6}});
    Matrix<double> second({{7,8},{9,10},{11,12}});
    Matrix<double> result(2,2);

    result = first * second;

    return 0;
}
