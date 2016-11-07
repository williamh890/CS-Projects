#include <iostream>
#include "include\Matrix.h"

using namespace std;

vector<int> name;

int main()
{
    Matrix<int> first(2,3,3);

    first.print();

    return 0;
}
