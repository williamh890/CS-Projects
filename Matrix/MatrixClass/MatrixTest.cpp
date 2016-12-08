//matrixtest.h
//William Horn
//11.29.2016
//Demo of matrix class features
//Group: William Horn, Orion Lust, Kyle Tam

#include "include\matrix.h"

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;


int main()
{
    Matrix<double> A("matrix1.txt");

    rref(A).print();

    return 0;
}









