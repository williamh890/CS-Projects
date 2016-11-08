#include <iostream>
#include "include\Matrix.h"

using namespace std;

vector<int> name;

int main()
{
    Matrix<int> first(2,3,3);
    Matrix<int> second(2,3,4);

    first = first + second;

    return 0;
}
