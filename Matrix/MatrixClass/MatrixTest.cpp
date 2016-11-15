#include <iostream>
#include "include\Matrix.h"

using namespace std;

vector<int> name;

int main()
{
    Matrix<double>  first({{1,2,3},
                           {4,5,6}});

    Matrix<double> second(2,3,9);

    Matrix<double> refTest({{3,-9,12,-9,6,15},
                           {3,-7,8,-5,8,9},
                           {0,3,-6,6,4,-5}});

    vector<double> r {2,2,3};
    vector<double> t {4,5,7};

    first.print();
    second.print();



    Matrix<double> result = transpose(second);
    result.print();

    cout << result.col;
    cout << result.row << endl;

    result = first + second;
    result.print();

    result += first;
    result.print();

    result = first - second;
    result.print();

    result -= first;
    result.print();

    second.resize(2,2);
    second.print();

    result = second * first;
    result.print();

    result.addRow({1,2,8});
    result.print();

    result.addRows(r,r,r,r,t,t,t,t,t,t,t);
    result.print();

    result.resize(2,2);
    result.print();


    ref(refTest).print();   //Prints the matrix through each step


    return 0;
}
