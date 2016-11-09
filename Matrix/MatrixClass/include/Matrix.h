#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <cassert>

template <typename T>
class Matrix
{
    int row;
    int col;
    std::vector<std::vector<T> > matrixVals;

    public:
        //Zero by default
        Matrix(int r = 0, int c = 0, T val = 0);
        Matrix(std::vector<std::vector<T> > data);

        ~Matrix();
        //Operations
        Matrix& operator+=(const Matrix& b);
        template <typename S>
        Matrix& operator*=(S scalar);
        Matrix<T>& operator*(Matrix<T> & B);

        void resize(int newRowSize, int newColSize, T fillvalue = 0);
        //Display
        inline at(int row, int col);
        void print();

    protected:

    private:
};
///////////////////////CTORS//////////////////////
template <typename T>
Matrix<T>::Matrix(int r, int c, T val) :  row(r), col(c)
{
    matrixVals.resize(r);
    for(int i = 0; i < (int)matrixVals.size(); ++i)
    {
        matrixVals[i].resize(c, val);
    }
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T> > data) : matrixVals(data)
{
    row = (int)matrixVals.size();
    col = (int)matrixVals[0].size();
}
/////////////////////////////////////////////////////////////


/////////////////////////////OPERATORS////////////////////////

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix & b)
{
    for(int r = 0; r < this->row; ++r)
    {
        for(int c = 0; c < this->col; ++c)
        {
            this->matrixVals[r][c] += b.matrixVals[r][c];
        }
    }
    return *this;
}

template <typename T>
Matrix<T>& operator+(Matrix<T> a, const Matrix<T> & b)
{
    return (a+=b);
}

template <typename T>
template <typename S>
Matrix<T>& Matrix<T>::operator*=(S scalar)
{
    for(int r = 0; r < this->row; ++r)
    {
        for(int c = 0; c < this->col; ++c)
        {
            this->matrixVals[r][c] *= (T)scalar;
        }
    }
    return *this;
}

template <typename T, typename S>
Matrix<T>& operator*(Matrix<T> a, S scalar)
{
    return (a*=(T)scalar);
}

template <typename T>
Matrix<T>& Matrix<T>::operator*(Matrix<T> & B)
{
    assert(this->col == B.row);
    //Matrix multiplication A*B
    Matrix<T> multResult(this->row,B.col,0);

    std::cout << this->row << " " << B.col << std::endl;

    T slot;
    for(int r = 0; r < multResult.row; ++r)
    {
        slot = 0;
        for(int c = 0; c < multResult.col; ++c)
        {
            slot = 0;
            for(int i = 0; i < B.row; ++i)
            {
                std::cout << B.row << std::endl;
                slot += (*this).matrixVals[r][i] * B.matrixVals[i][c];
            }
            multResult.matrixVals[r][c] = slot;
        }

    }
    multResult.print();

    return multResult;
}


///////////////////////////////////////////////////////////////////

///////////////////////////FUCNTIONALITY///////////////////////////

template <typename T>
void Matrix<T>::resize(int newNumRows, int newNumCols, T fillValue)
{
    //std::vector<std::vector<T> > data

    if(newNumCols > this->col)
    {
        //Add new values (zero by default) to the end of all row vectors
        for(auto & r : this->matrixVals)
        {
            r.insert(r.end(), (newNumCols - this->col), fillValue);
        }

    }
    if(newNumCols < this->col)
    {
        //Remove appropriate number of ending rows
        //Erase the ending values
        for(auto & r: this->matrixVals)
        {
            r.resize(newNumCols);
        }
    }

    if(newNumRows > this->row)
    {
        std::vector<T> newRows(newNumCols, fillValue);
        this->matrixVals.insert(matrixVals.end(), (newNumRows - this->row), newRows);
    }
    if(newNumRows < this->row)
    {

    }
    this->col = newNumCols;
    this->row = newNumRows;
}

template <typename T>
void Matrix<T>::print()
{
    if(this->row == 0 || this->col == 0) {std::cout << std::endl << "[Empty Matrix]" << std::endl; return;}

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
    std::cout << std::endl;
}

template <typename T>
inline Matrix<T>::at(int row, int col)
{
    return this->matrixVals[row][col];
}

template <typename T>
Matrix<T>::~Matrix()
{
    //dtor
}

#endif // MATRIX_H
