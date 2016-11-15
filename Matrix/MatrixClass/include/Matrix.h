#ifndef MATRIX_H
#define MATRIX_H

#include <vector> //vector
#include <iostream> //cout
#include <cassert> //assert
#include <stdlib.h> //abs
#include <utility> //pair, make_pair
#include <iomanip>

template <typename T>
class Matrix
{
    public:
        std::vector<std::vector<T> > matrixVals;
        unsigned int row = (int)matrixVals.size();
        unsigned int col = (int)matrixVals[0].size();
        ////////////////CTORS//////////////
        Matrix(int r = 0, int c = 0, T val = 0);
        Matrix(std::vector<std::vector<T> > data);

        ~Matrix();
        //////////////Operations/////////////
        std::vector<T> operator[](size_t i);
        Matrix& operator+=(const Matrix & b);
        Matrix& operator-=(const Matrix & b);
        Matrix& operator*=(T scalar);
        Matrix<T>& operator*=(Matrix<T> & B);

        ///////////////////Utility//////////////////
        void resize(int newRowSize, int newColSize, T fillvalue = 0);
        //Adding Row/Rows
        void addRow(std::vector<T> row);
        void addRows(std::vector<T> row);
        template<typename...Rs>
        void addRows(std::vector<T> row, Rs...rows);
        //Adding Col/Cols
        void addCol(std::vector<T> col);
        void addCols(std::vector<T> col);
        template<typename ...Cs>
        void addCols(std::vector<T> col, Cs...cols);
        ////////////////////////////////////////////

        ////////////////Display/////////////////
        void print();

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

////////////////Adding cols///////////////
template <typename T>
void Matrix<T>::addCol(std::vector<T> col)
{
    assert(col.size() == matrixVals.size());
    for(int i = 0; i < matrixVals.size(); ++i)
    {
        matrixVals[i].push_back(col[i]);
    }
    this->row = (int)matrixVals.size();
    this->col = (int)matrixVals[0].size();
}
//for the last vector in the  pack
template <typename T>
void Matrix<T>::addCols(std::vector<T> col)
{
    addCol(col);
}
template <typename T>
template<typename ...Cs>
void Matrix<T>::addCols(std::vector<T> col, Cs...cols)
{
    addCol(col);
    addCols(cols...);
}
////////////////////////////////////////

////////////Adding rows////////////////
template <typename T>
void Matrix<T>::addRow(std::vector<T> row)
{
    assert(row.size() == matrixVals[0].size());
    matrixVals.push_back(row);
    this->row = (int)matrixVals.size();
    this->col = (int)matrixVals[0].size();
}
//for the last vector in the  pack
template <typename T>
void Matrix<T>::addRows(std::vector<T> row)
{
    addRow(row);
}
//Unknown number of vectors packed
template <typename T>
template<typename ...Rs>
void Matrix<T>::addRows(std::vector<T> row, Rs...rows)
{
    addRow(row);
    addRows(rows...);
}
////////////////////////////////////////

//////////////////ref//////////////////
//Row reduce a matrix to reduced echelon form
template <typename T>
bool correct(Matrix<T> A ,std::vector<std::pair<int,int> > pivotPositions)
{
    for(int i = 0; i < pivotPositions.size(); ++i)
    {
        int currRow = pivotPositions[i].first;
        int currCol = pivotPositions[i].second;

        if(A.matrixVals[currRow][currCol] != 1) return false;
        for(int r = currRow - 1; r >= 0; --r)
        {
            if(A.matrixVals[r][currCol] != 0) return false;
        }
    }
    return true;
}

template <typename T>
Matrix<T>& rref(Matrix<T> A)
{
    //Number of entries in each column
    int entriesPerCol = A.row;
    //Number of entries in each row
    int entriesPerRow = A.col;
    //Current column being looked at
    int currPivotCol = 0;
    int currPivotRow = 0;

    std::vector<std::pair<int,int> > pivotPositions;
    while(currPivotCol < entriesPerCol)
    {
        //STEP 1
        //Begin with the leftmost nonzero col. This is a pivot column. The pivot position is at the top.

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

        while(1)  //Loop to select pivot col
        {
            A.print();
            bool zeroCol = true;
            for(int i = currPivotRow; i < entriesPerCol; ++i)
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
        A.print();
        if(pivotPosition != currPivotRow)
        {
            A.print();
            A.matrixVals[currPivotRow].swap(A.matrixVals[pivotPosition]);
            pivotPosition = currPivotRow;
            for (auto n : pivotPositions)
            {
                std::cout << n.first << " " << n.second << std::endl << std::endl;
            }
        }
        pivotPositions.push_back(std::make_pair(currPivotRow,currPivotCol));
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

        currPivotCol++;
        currPivotRow++;
    }
    pivotPositions.push_back(std::make_pair(currPivotRow,currPivotCol));
    for (auto n : pivotPositions)
    {
        std::cout << n.first << " " << n.second << std::endl;
    }

    A.print();

    //Scales all the pivot cols to 1
    for(int i = pivotPositions.size() - 1; i >= 0; --i)
    {
        A.print();
        //Value used to determine scale
        T currPivVal = A.matrixVals[pivotPositions[i].first][pivotPositions[i].second];
        //Location of the pivot position
        int currPivRow = pivotPositions[i].first;
        int currPivCol = pivotPositions[i].second;

        T scale;
        //Determine the value to scale the whole row by
        if(currPivVal == 1)         continue;
        else if(currPivVal > 1)     scale = currPivVal;
        else if(currPivVal < 1)     scale = -currPivVal;
        //Walk through the row and multiply by the scale
        for(int c = pivotPositions[i].second; c < A.matrixVals[0].size(); ++c)
        {
            A.matrixVals[currPivRow][c] *= (1/scale);
        }
        //Every pivot position has a value of 1
    }
//    for(int i = pivotPositions.size() - 1; i >= 0; --i)
//    {
//        int currPivRow = pivotPositions[i].first;
//        int currPivCol = pivotPositions[i].second;
//
//        T currPivVal = A.matrixVals[pivotPositions[i].first][pivotPositions[i].second];
//
//        //Runs through all the rows and finds the correct scale to zero out the position
//        for(int r = 0; r < currPivRow ; ++r)
//        {
//            //Scale to zero out col
//            T scale = -currPivVal*A.matrixVals[r][currPivCol];
//
//            //Runs through all the entries in the row and multiplies them by the scale
//            for(int c = currPivCol; c < A.matrixVals[0].size(); ++c)
//            {
//                A.matrixVals[r][c] += scale * (A.matrixVals[currPivRow][c]);
//                T currPosVal = A.matrixVals[r][c];
//            }
//        }
//    }

    return A;
}
/////////////////////////////////

template <typename T>
Matrix<T>& invert(Matrix<T> A)
{
    //Add I_d matrix to the end of the existing matrix
    //
    for(int i = 0; i < A.matrixVals.size(); ++i)
    {

    }
}

//////////Determinant////////////
template <typename T>
T determinant(const Matrix<T> A){
	//if matrix isn't square dont bother
	assert(A.row == A.col);
	//get the size of the matrix
	int size= A.row;
	int det;
	int cofactor;
	//1 by 1
	if(size==1){
		return A.matrixVals[0][0];
	}
	//lambda function for 2by 2
	auto det2=[](Matrix<T> subA){ return (subA.matrixVals[1][1]*subA.matrixVals[0][0]-subA.matrixVals[1][0]*subA.matrixVals[0][1]);};

		if(size>2){ /////cofactor

            std::vector<Matrix<T>> submatricies;
            bool negative=false;
        ///////////
        while(submatricies[0].matrixVals.size()>2){
			for(int k=0;k<A.matrixVals.size();k++){
                cofactor=A.matrixVals[0][k];

                    for(int j=0;j<A.matrixVals.size();j++){
                        if(j==k)
                            continue;
                        for(int l=0; l <A.matrixVals.size();l++){
                            if(l==k)
                                continue;
                            submatricies.push_back(A.matrixVals[j][k]);
                        }
                    }



                if(negative){
                    cofactor*=-1;
                    negative=false;
                }else{
                    negative=true;
                }
			}
        }
			///////////////////////
		}
	//for 2by2
	if(size==2){
		return det2(A);
	}


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

//////////////Transpose///////////////
template <typename T>
Matrix<T>& transpose(Matrix<T> A)
{
    Matrix<T> A_t(A.col, A.row);    //Makes the right sized transposed vector

    for(int i = 0; i < A.matrixVals.size(); ++i)
        for(int j = 0; j < A.matrixVals[0].size(); ++j)
            A_t.matrixVals[j][i] = A.matrixVals[i][j];  //Switch the rows with the cols

    A = A_t;    //So the address can be returned properly
    return A;
}

template <typename T>
Matrix<T>::~Matrix()
{
    //dtor
}

#endif // MATRIX_H
