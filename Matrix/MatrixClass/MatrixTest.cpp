#include <iostream>
#include "include\Matrix.h"

using namespace std;

int main()
{
    Matrix<double> Default(2,2,1);

    Matrix<double> A({{ 1, 2 },
                      { 4, 5 }});

    Matrix<float> T({{ 1, 3, 5 },
                     { 2, 1, 1 },
                     { 3, 4, 2 }});

    Matrix<long double> F({{  70,  19,  2.5,  -8,    9    },
                           { -9.5,  11, -80,   8, -70.05  },
                           { -33, -66, -4.9, -89,  -13    },
                           {  .96, -82, -16,   2,  -7.9   },
                           { -28, -2.1,  12,  65,   17    }});

    Matrix<double> B({{ 1, 2, 4,  8 },
                      { 2, 4, 6,  8 },
                      { 3, 6, 9, 13 }});

    Matrix<double> C({{ 1,  3,     1,        5   },
                      { 5, 20,     6,       31   },
                      {-2, -1,    -1,       -4   },
                      { 2, 10, -0.000042, 5002.16}});

    Matrix<double> D({{   7,  -6,  1,   6  },
                      {   2, .02, -1, 9.78 },
                      {  -3,   4, -6, -14  },
                      { 2.5,   2,  7,   1  }});

    Matrix<double> R ({{ 0,  3, -6,  6, 4, -5 },
                       { 3, -7,  8, -5, 8,  9 },
                       { 3, -9, 12, -9, 6, 15 }});

    Matrix<long double> E({{  1,  9,   8, 0 },
                           {  6, -6, -12, 0 },
                           { -5,  1,   6, 0 },
                           {  1,  0,  -1, 0 }});

    Matrix<int> Z(3,5);

    Matrix<double> result;

    cout << "|**********MATRIX CLASS DEMO***********|\n" << endl;
    //operators

    cout << "Result = A + (2*A)" << endl;
    result = A + (2.*A);
    result.print();

    cout << "result = B - B" << endl;
    result = B - B;
    result.print();

    cout << "C * D" << endl;
    (C * D).print();

    cout << "B.resize(2,3)" << endl;
    B.resize(2,3);
    B.print();

    cout << "B.addCol({8, 8})" << endl;
    B.addCol({8,8});
    B.print();

    cout << "B.addRow({3, 6, 9, 13})" << endl;
    B.addRow({3,6,9,13});
    B.print();

    vector<double> r1 {3, 6, 9, 13};
    vector<double> r2 {5, 5, -1, 7};

    cout << "r1: 3, 6, 9, 13\nr2: 5, 5, -1 7\n\n"
         << "B.addRows(r1,r2,r1,r1,r1,r2)" << endl;
    B.addRows(r1,r2,r1,r1,r1,r2);
    B.print();

    B.resize(4,4);

    cout << "B.addCols(r1,r2,r1,r1,r1,r2)" << endl;
    B.addCols(r1,r2,r1,r1,r1,r2);
    B.print();

    B.resize(4,4);

    cout << "B" << endl;
    B.print();

    cout << "B.interchange(0,1)" << endl;
    B.interchange(0,1);
    B.print();

    cout << "B.scale(3, 2)" << endl;
    B.scale(3,2);
    B.print();

    cout << "B.replacement(2,1,-2)" << endl;
    B.replacement(2,1,-2);
    B.print();

    cout << "R" << endl;
    R.print();

    cout << "rref(R)" << endl;
    rref(R).print();

    cout << "rref(transpose(R))" << endl;
    rref(transpose(R)).print();

    cout << "E";
    E.print();

    cout << "rref(E)" << endl;
    rref(E).print();

    cout << "D";
    D.print();

    cout << "rref(D)" << endl;
    rref(D).print();

    cout << "invert(D)" << endl;
    invert(D).print();

    cout << "A";
    A.print();
    cout << "det(A) = " << det(A) << endl;

    cout << "T";
    T.print();
    cout << "det(T) = " << det(T) << endl << endl;

    cout << "F";
    F.print();
    cout << "det(F) = " << det(F) << endl;

    return 0;
}









