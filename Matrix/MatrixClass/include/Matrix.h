#ifndef MATRIX_H
#define MATRIX_H

#include <vector> //vector
#include <iostream> //cout
#include <cassert> //assert
#include <stdlib.h> //abs

template <typename T>
class Matrix
{


    public:
        std::vector<std::vector<T> > matrixVals;
        int row;
        int col;
        //Zero by default
        Matrix(int r = 0, int c = 0, T val = 0);
        Matrix(std::vector<std::vector<T> > data);

        ~Matrix();
        //Operations
        std::vector<T> operator[](size_t i);
        Matrix& operator+=(const Matrix & b);
        Matrix& operator-=(const Matrix & b);
        Matrix& operator*=(T scalar);
        Matrix<T>& operator*=(Matrix<T> & B);


        void resize(int newRowSize, int newColSize, T fillvalue = 0);
        //Display
        void print();

    protected:

    private:
};
///////////////////////CTORS/////////////////////////
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
std::vector<T> Matrix<T>::operator[](size_t i)  //Indexing
{
    return matrixVals[i];
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix & b)  //Addition
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
Matrix<T>& operator+(Matrix<T> a, const Matrix<T> & b)  //Addition
{
    return (a+=b);
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix & b)  //Subtraction
{
    for(int r = 0; r < this->row; ++r)
    {
        for(int c = 0; c < this->col; ++c)
        {
            this->matrixVals[r][c] -= b.matrixVals[r][c];
        }
    }
    return *this;
}

template <typename T>
Matrix<T>& operator-(Matrix<T> a, Matrix<T> b)  //Subtraction
{
    return (a-=b);
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T scalar)  //Scalar Multiplication
{
    for(int r = 0; r < this->row; ++r)
    {
        for(int c = 0; c < this->col; ++c)
        {
            this->matrixVals[r][c] *= scalar;
        }
    }
    return *this;
}

template <typename T>
Matrix<T>& operator*(Matrix<T> a, T scalar) //Scalar Multiplication
{
    return (a*=scalar);
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(Matrix<T> & B) //Matrix Multiplication
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
    //Copies the data from the temp matrix into the this matrix
    //Only way to return without getting std::bad_alloc
    (*this).matrixVals.swap(multResult.matrixVals);

    return *this;
}

template <typename T>
Matrix<T>& operator*(Matrix<T> a, Matrix<T> b)  //Matrix Multiplication
{
    return (a*=b);
}


///////////////////////////////////////////////////////////////////

///////////////////////////FUCNTIONALITY///////////////////////////

//Resize a matrix by adding rows/cols full of an indicated value
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
        //Makes new rows and fills them with a desired value
        std::vector<T> newRows(newNumCols, fillValue);
        this->matrixVals.insert(matrixVals.end(), (newNumRows - this->row), newRows);
    }
    if(newNumRows < this->row)
    {
        //Resize the matrix, deletes rows to make space
        this->matrixVals.resize(newNumRows);
    }
    //Sets the number of col and rows to there new values
    this->col = newNumCols;
    this->row = newNumRows;
}

//Row reduce a matrix to reduced echelon form
template <typename T>
Matrix<T>& ref(Matrix<T> A)
{
    //Number of entries in each column
    int entriesPerCol = A.row;
    //Number of entries in each row
    int entriesPerRow = A.col;
    //Current column being looked at
    int currPivotCol = 0;
    int currPivotRow = 0;
    while(currPivotCol < entriesPerCol)
    {
        //STEP 1
        //Begin with the leftmost nonzero col. This is a pivot column. The pivot position is at the top.

        while(1)  //Loop to select pivot col
        {
            A.print();
            bool zeroCol = true;
            for(int i = 0; i < entriesPerCol; ++i)
            {
                if(A.matrixVals[i][currPivotCol] != 0) zeroCol = false;
            }
            if(zeroCol)++currPivotCol;
            else break;
        }
        //Select the largest value to be the pivot position
        int largestColPosValue = 0;
        int pivotPosition;
        for(int i = currPivotRow; i < entriesPerCol; ++i)
        {
            if(abs(A.matrixVals[i][currPivotCol]) > largestColPosValue)
            {
                largestColPosValue = A.matrixVals[i][currPivotCol];
                pivotPosition = i;
            }
        }
        //Pivot position with the largest value has been selected

        //Moves the row with the pivot position to the top if not already
        if(pivotPosition != currPivotRow)
        {
            A.matrixVals[currPivotRow].swap(A.matrixVals[pivotPosition]);
            pivotPosition = currPivotRow;
            A.print();
        }
        //pivot pos row at the top

        bool negPivot = (largestColPosValue < 0);
        //goes through and zeros out values underneath the pivot position
        for(int i = currPivotRow + 1; i < entriesPerCol; ++i)
        {
            T scale;
            //Determine the value to scale the whole row by
            if(A.matrixVals[i][currPivotCol] == 0) continue; //The value is already zero

            if     ((A.matrixVals[i][currPivotCol] > 0 && !negPivot) ||
                    (A.matrixVals[i][currPivotCol] < 0 && !negPivot) ||
                    A.matrixVals[i][currPivotCol] == largestColPosValue)
                                scale = -(largestColPosValue / A.matrixVals[i][currPivotCol]);  //Multiply by the -reciprocal

            else if (A.matrixVals[i][currPivotCol] > 0 && negPivot) //Values already have opposite signs
                                scale = (largestColPosValue / A.matrixVals[i][currPivotCol]);

            if(A.matrixVals[i][currPivotCol] != 0)
            {
                for(int r = 0; r < entriesPerRow; ++r)
                {
                    A.matrixVals[i][r] *= scale;
                    A.matrixVals[i][r] += A.matrixVals[pivotPosition][r];
                }
            }
        }
        A.print();
        currPivotCol++;
        currPivotRow++;
    }




    //STEP 2
    //Select a nonzero entry in the pivot col as a pivot.
    //If necessary, interchange rows to move this entry into the pivot position

    //STEP 3
    //Use row replacement operations to create zeros in all positions below the pivot.

    //STEP 4
    //Ignore the row containing the pivot position and cover all rows, if any, above it.
    //Apply steps 1-3 to the sub matrix that remains.
    // Repeat the process unit there are no more nonzero rows to modify

    //STEP 5
    //Beginning with the rightmost pivot and working upward and to the left,
    //create zeros above each pivot. If a pivot is not 1, make it 1 by a scaling operation

    return A;
}

//Simply print out a matrix
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
Matrix<T>::~Matrix()
{
    //dtor
}

#endif // MATRIX_H
