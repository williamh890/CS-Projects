#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>


template <typename T>
class Matrix
{
    int row;
    int col;
    std::vector<std::vector<T> > matrixVals;

    public:
        //Zero by default
        Matrix(int r, int c);
        Matrix(int r, int c, T val);
        Matrix(std::vector<std::vector<T> > data);

        ~Matrix();
        //Operations
        Matrix& operator+(const Matrix& b);

        //Display
        void print();

    protected:

    private:
};

template <typename T>
Matrix<T>::Matrix(int r, int c) : row(r), col(c)
{
    matrixVals.resize(r);
    for(int i = 0; i < matrixVals.size(); ++i)
    {
        matrixVals[i].resize(c, 0);
    }
}

template <typename T>
Matrix<T>::Matrix(int r, int c, T val)
{
    matrixVals.resize(r);
    for(int i = 0; i < matrixVals.size(); ++i)
    {
        matrixVals[i].resize(c, val);
    }
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T> > data) : matrixVals(data)
{
    row = (int)matrixVals.size();
    col = (int)matrixVals.size();
}

template <typename T>
Matrix<T>& Matrix<T>::operator+(const Matrix & b)
{
    Matrix matrixSum(this->row, this->col);
    for(int r = 0; r < this->row; ++r)
    {
        for(int c = 0; c < this->col; ++c)
        {
            matrixSum.matrixVals[r][c] = this->matrixVals[r][c] + b.matrixVals[r][c];
        }
    }
    return matrixSum;
}

template <typename T>
void Matrix<T>::print()
{
    std::cout << std::endl;
    for(auto r : matrixVals)
    {
        std::cout << " ";
        for(auto c : r )
        {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
Matrix<T>::~Matrix()
{
    //dtor
}

#endif // MATRIX_H
