//matrix.h
//William Horn
//10.29.2016
//Matrix class
//Group: William Horn, Orion Lust, Kyle Tam

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>    //vector
#include <iostream>  //cout
#include <cassert>   //assert
#include <cmath>     //abs, round
#include <utility>   //pair, make_pair
#include <iomanip>   //setprecision
#include <sstream>   //ostringstream
#include <string>    //string

#define ZERO_LIMIT (1e-10)

/*
    I had never done a project this big before, and I soon realized that
    the choices made in the beginning of the class's creation greatly
    affect the later functions. If I were to make the class I would have made
    _matrixVals, _rows, and _cols protected and used functions to access them.
    Also, I need to find a way to hide the internal sub-functions used in the calculation
    functions from the outside world.

    This project is in no way complete, and as I am quickly finding out
    with coding, they never are, but you have to call it somewhere so...
    here you go.

    Enjoy!
*/

template <typename T>
class Matrix
{
    public:
        std::vector<std::vector<T> > _matrixVals;
        unsigned int _rows; //Number of rows
        unsigned int _cols; //Number of columns
        ///////////////////CTORS////////////////////

        Matrix() = default;
        Matrix(unsigned int r,unsigned int c, T val = 0);
        Matrix(std::vector<std::vector<T> > data);

        virtual ~Matrix() = default; //DTOR
        //////////////Operations////////////////////
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
        ////////////Elementary Row Ops////////////////
        void replacement(int curRow, int otherRow, T otherRowScale);
        void interchange(int row1, int row2);
        void scale(int row, T scale);
        ////////////////Display//////////////////////
        void print() const;
        std::pair<unsigned int, unsigned int> size();

        //////////Calculation Functions/////////////
   /*********************************************************
    *  Matrix<T> rref(Matrix<T> A, bool debug = false);     *
    *  Matrix<T> invert(Matrix<T> A)                        *
    *  T det(Matrix<T> A)                                   *
    *  Matrix<T> transpose(Matrix<T> A)                     *
    *********************************************************/

}; //END MATRIX
///////////////////////CTORS/////////////////////////
//Construct a matrix of a desired size

template <typename T>
Matrix<T>::Matrix(unsigned int r,unsigned int c, T val) :  _rows(r), _cols(c)
{
    assert(r > 0);
    assert(c > 0);

    _matrixVals.resize(r);
    for(int i = 0; i < (int)_matrixVals.size(); ++i)
    {
        _matrixVals[i].resize(c, val);
    }
    _rows = (int)_matrixVals.size();
    _cols = (int)_matrixVals[0].size();
}
//Construct a matrix with a vector of vectors
template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T> > data) : _matrixVals(data)
{
    _rows = (int)_matrixVals.size();
    _cols = (int)_matrixVals[0].size();
}
/////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////OPERATORS////////////////////////////////////////////////////////////////////
template <typename T>
std::vector<T> Matrix<T>::operator[](size_t i)  //Indexing
{
    return _matrixVals[i];
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix & b)  //Addition
{
    for(int r = 0; r < (int)this->_rows; ++r)
    {
        for(int c = 0; c < (int)this->_cols; ++c)
        {
            this->_matrixVals[r][c] += b._matrixVals[r][c];
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
    for(int r = 0; r < (int)this->_rows; ++r)
    {
        for(int c = 0; c < (int)this->_cols; ++c)
        {
            this->_matrixVals[r][c] -= b._matrixVals[r][c];
        }
    }
    return *this;
}

template <typename T>
Matrix<T>& operator-(Matrix<T> a, const Matrix<T> & b)  //Subtraction
{
    return (a-=b);
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T scalar)  //Scalar Multiplication
{
    for(int r = 0; r < (int)this->_rows; ++r)
    {
        for(int c = 0; c < (int)this->_cols; ++c)
        {
            this->_matrixVals[r][c] *= scalar;
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
Matrix<T>& operator*(T scalar, Matrix<T> a) //Scalar Multiplication
{
    return (a*=scalar);
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(Matrix<T> & B) //Matrix Multiplication
{
    assert(this->_cols == B._rows);
    //Matrix multiplication A*B
    Matrix<T> multResult(this->_rows,B._cols,0);


    T slot;
    for(int r = 0; r < (int)multResult._rows; ++r)
    {
        for(int c = 0; c < (int)multResult._cols; ++c)
        {
            slot = 0;
            for(int i = 0; i < (int)B._rows; ++i)
            {
                slot += (*this)._matrixVals[r][i] * B._matrixVals[i][c];
            }
            multResult._matrixVals[r][c] = slot;
        }
    }

    //Copies the data from the temp matrix into the this matrix
    //Only way to return without getting std::bad_alloc
    (*this)._matrixVals.swap(multResult._matrixVals);

    return *this;
}

template <typename T>
Matrix<T>& operator*(Matrix<T> a, Matrix<T> b)  //Matrix Multiplication
{
    return (a*=b);
}
///////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////FUCNTIONALITY////////////////////////////////////////////////////////////////

//Resize a matrix by adding rows/cols full of an indicated value
template <typename T>
void Matrix<T>::resize(int newNumRows, int newNumCols, T fillValue)
{
    //std::vector<std::vector<T> > data

    if(newNumCols > (int)this->_cols)
    {
        //Add new values (zero by default) to the end of all row vectors
        for(auto & r : this->_matrixVals)
        {
            r.insert(r.end(), (newNumCols - this->_cols), fillValue);
        }
    }
    if(newNumCols < (int)this->_cols)
    {
        //Remove appropriate number of ending rows
        //Erase the ending values
        for(auto & r: this->_matrixVals)
        {
            r.resize(newNumCols);
        }
    }
    if(newNumRows > (int)this->_rows)
    {
        //Makes new rows and fills them with a desired value
        std::vector<T> newRows(newNumCols, fillValue);
        this->_matrixVals.insert(_matrixVals.end(), (newNumRows - this->_rows), newRows);
    }
    if(newNumRows < (int)this->_rows)
    {
        //Resize the matrix, deletes rows to make space
        this->_matrixVals.resize(newNumRows);
    }
    //Sets the number of _cols and rows to there new values
    this->_cols = newNumCols;
    this->_rows = newNumRows;
}

//Modifies the original matrix
//Takes a pair of the top left and the bottom Right coordinates and makes a sub matrix
//First is the row, Second is the column

////////////////Adding cols///////////////
template <typename T>
void Matrix<T>::addCol(std::vector<T> col)
{
    assert(col.size() == _matrixVals.size());
    for(int i = 0; i < (int)_matrixVals.size(); ++i)
    {
        _matrixVals[i].push_back(col[i]);
    }
    this->_rows = (int)_matrixVals.size();
    this->_cols = (int)_matrixVals[0].size();
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
    assert(row.size() == _matrixVals[0].size());
    _matrixVals.push_back(row);
    this->_rows = (int)_matrixVals.size();
    this->_cols = (int)_matrixVals[0].size();
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
///////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////Elementary Row Operations///////////////////////////////////////////////////////////

//Swqp two rows
template <typename T>
void Matrix<T>::interchange(int row1, int row2)
{
    _matrixVals[row1].swap(_matrixVals[row2]);
}
//scales a row by a value
template <typename T>
void Matrix<T>::scale(int rowNum, T scale)
{
    assert(rowNum >= 0 &&  rowNum < (int)_matrixVals[0].size());

    for(auto & r : _matrixVals[rowNum])
    {
        r *= scale;
    }
}
//replace curRow row with the sum of that row plus the multiple of another row
template <typename T>
void Matrix<T>::replacement(int curRow, int otherRow, T otherRowScale)  //Current row gets changed
{
    for(int i = 0; i < (int)_matrixVals[0].size(); ++i)
    {
        _matrixVals[curRow][i] = _matrixVals[curRow][i] + (otherRowScale * _matrixVals[otherRow][i]);
    }
}

///////Functions used in rref//////////
//Checks if the column is only zeros
template <typename T>
bool zeroColumn(Matrix<T> A, int currPivotRow, int currPivotCol)
{
    //Assumes zero column
    bool isZeroCol = true;
    //Runs through column and checks if any value is not zero
    for(int r = currPivotRow; r < (int)A._matrixVals.size(); ++r)
    {
        //If a value is not zero, then break
        if(!(A[r][currPivotCol] > -ZERO_LIMIT && A[r][currPivotCol] < ZERO_LIMIT))
        {
            isZeroCol = false;
            break;
        }
    }
    return isZeroCol;
}
//Checks if the row is only zeros
template <typename T>
bool zeroRow(Matrix<T> A, int currPivotRow)
{
    bool isZeroRow = true;
    //Runs through row and check is any value is not zero
    for(int c = 0; c < (int)A[0].size(); ++c)
    {
        if(!(A[currPivotRow][c] > -ZERO_LIMIT && A[currPivotRow][c] < ZERO_LIMIT))
        {
            isZeroRow = false;
            break;
        }
    }
    return isZeroRow;
}
//Gives the row position of the largest value in that column
template <typename T>
int largest_value_position(Matrix<T> A, int currPivotRow, int currPivotCol, int exitRow)
{
    int largestValPos = 0;
    T largestVal = 0;
    //Runes through the values under the row
    for(int r = currPivotRow; r < exitRow; ++r)
    {
        if(std::abs(A[r][currPivotCol]) > std::abs(largestVal))
        {
            largestValPos = r;
            largestVal = std::abs(A[r][currPivotCol]);
        }
    }
    return largestValPos;
}
//Moves the a zero row to the bottom of the matrix
template <typename T>
void zero_row_to_bottom (Matrix<T> & A, int currPivotRow)
{
    assert(zeroRow(A, currPivotRow));
    //Erase the zero row
    A._matrixVals.erase(A._matrixVals.begin() + currPivotRow);
    //Adds a zero row to the end
    std::vector<T> zeros(A[0].size(), 0);
    A._matrixVals.push_back(zeros);
}
//Move value found by largest_value_position to the top most pivot row
template <typename T>
void move_pivot_to_top(Matrix<T> & A, int currPivotRow, int largestValueRow)
{
    //Moves largest valued row to the top
    A._matrixVals[currPivotRow].swap(A._matrixVals[largestValueRow]);
}
//Scales the pivot value to one, by scale the row with the appropriate value
template <typename T>
void scale_pivot_row_to_1(Matrix<T> & A, int currPivotRow, int currPivotCol)
{
    if(zeroRow(A, currPivotRow)) return;

    T pivotPositionVal = A[currPivotRow][currPivotCol];
    T rowScale;
    //Determines the value needed to scale pivot by
    if     (pivotPositionVal == 1) return;
    else if(pivotPositionVal  > 0) rowScale =  1 / pivotPositionVal;
    else    /*value is negative*/  rowScale = -1 / std::abs(pivotPositionVal);

    //Performs the operation
    A.scale(currPivotRow, rowScale);
    //Pivot position should be 1

}
//Zeros out the values above and below the pivot position
template <typename T>
void zero_out_above_and_below(Matrix<T> & A, int currPivotRow, int currPivotCol, int exitRow)
{
    //zero pivot col, except piv position
    for(int r = 0; r < (int)A._matrixVals.size(); ++r)
    {
        //skips zeroing out pivot row, or if value already zero
        if(r == currPivotRow) continue;
        if((A[r][currPivotCol] > -ZERO_LIMIT && A[r][currPivotCol] < ZERO_LIMIT)) continue;

        A.replacement(r, currPivotRow, -A[r][currPivotCol]);
    }
}
////////////////////////////////////////////////////////////////////ROW REDUCED ECHELON FORM////////////////////////////////////////////////////////////////////
template <typename T>
Matrix<T> rref(Matrix<T> A)
{
    //Starts at the top left of the matrix
    int currPivotCol = 0;
    int currPivotRow = 0;

    //By default exits at the last row
    int exitRow = (int)A._matrixVals.size();
    bool isDone = false;
    //Row reduction
    while(currPivotRow != exitRow)
    {
        //Checks for a zero row
        while(true)
        {
            //If row of zeros, move to the bottom and add 1 to the exit row
            if(zeroRow(A,currPivotRow))
            {
                zero_row_to_bottom(A, currPivotRow);
                --exitRow;
            }
            //Makes sure the next row isn't also a zero row
            if(!zeroRow(A,currPivotRow)) break;
            //Checks to see if done
            if(currPivotRow >= exitRow)
            {
                isDone = true;
                break;
            }
        }
        if(isDone) break;

        //If all zeros in pivot position
        while(true)
        {
            if(zeroColumn(A,currPivotRow,currPivotCol)) ++currPivotCol;
            if(currPivotCol == (int)A._cols || !zeroColumn(A,currPivotRow,currPivotCol)) break;
        }
        //finds the row position largest value in the pivot column
        //Returns the row that has the largest value
        int largestValueRow = largest_value_position(A,currPivotRow,currPivotCol, exitRow);
        //Move the largest value row to the top
        move_pivot_to_top(A, currPivotRow, largestValueRow);

        scale_pivot_row_to_1(A, currPivotRow, currPivotCol);

        zero_out_above_and_below(A, currPivotRow, currPivotCol, exitRow);

        ++currPivotRow;
    }
    return A;
}
/////////////////////END RREF////////////////////

////////////////////////////////////////////////////////////////////INVERT//////////////////////////////////////////////////////////////////
//Adds id matrix to the left size of matrix
template <typename T>
void add_id(Matrix<T> & A)
{
    //Creates vector of zeros
    std::vector<T> id_Row(A[0].size(), 0);
    //Loops through all the rows
    for(int r = 0, id_c = 0; r < (int)A._matrixVals.size(); ++r, ++id_c)
    {
        //Puts a one in the vec
        id_Row[id_c] = 1;
        //Tacks it onto the end of the matrix
        A._matrixVals[r].insert(A._matrixVals[r].end(), id_Row.begin(), id_Row.end());
        //Sets the vector back to zero
        id_Row.assign(id_Row.size(), 0);
    }
}

//Remove id from the right side of matrix
template <typename T>
void remove_id(Matrix<T> & A)
{
    for(int r = 0; r < (int)A._matrixVals.size(); ++r)
    {
        A._matrixVals[r].erase(A._matrixVals[r].begin(), A._matrixVals[r].begin() + (A[r].size()/2));
    }
}

//Find the inverse of a matrix
template <typename T>
Matrix<T> invert(Matrix<T> A)
{
    //Make sure the matrix is actually invertible
    assert(det(A) != 0);

    add_id(A);
    A = rref(A);
    remove_id(A);
    return A;
}
////////////////END INVERSE////////////////

////////////////DETERMINANT/////////////////////

//Find the det of a 2x2 matrix
template <typename T>
T det2_2(Matrix<T> A)
{
    return ((A[0][0] * A[1][1]) - (A[0][1] * A[1][0]));
}

//Matrix class but with a cofactor value associated with it
//Ctor used to create smaller cofactors from larger ones
template <typename T>
class Cofactor : public Matrix<T>
{
public:
    T cofactorValue;

    Cofactor(T cofacVal, int cofacCol, Matrix<T> Derived) : Matrix<T>(Derived._matrixVals), cofactorValue(cofacVal)
    {
        //Erases the top row
        this->_matrixVals.erase(this->_matrixVals.begin());

        //Erase the col from the cofactor
        for(int i = 0; i < (int)this->_matrixVals.size(); ++ i)
        {
            this->_matrixVals[i].erase(this->_matrixVals[i].begin() + cofacCol);
        }
        this->_rows = (int)this->_matrixVals.size();
        this->_cols = (int)this->_matrixVals[0].size();
    }

};
//Break a martix down into smaller cofactors
//Used for the initial cofactor of the input matrix
template <typename T>
std::vector<Cofactor<T> > cofactor_matrix(const Matrix<T> & A)
{
    std::vector<Cofactor<T> > cofactors;
    //Create the cofactors down the first column
    for(int r = 0; r < (int)A._rows; ++r)
    {
        Cofactor<T> newCofactor(A._matrixVals[0][r] * pow(-1,(r+1)+1), r, A);
        cofactors.push_back(newCofactor);
    }
    return cofactors;
}

//Break a martix down into smaller cofactors
//This version is for cofactoring cofactors.
template <typename T>
std::vector<Cofactor<T> > cofactor_matrix(const Cofactor<T> & A)
{
    std::vector<Cofactor<T> > cofactors;
    //Create the cofactors down the first column
    for(int r = 0; r < (int)A._rows; ++r)
    {
        Cofactor<T> newCofactor(A._matrixVals[0][r] * pow(-1,(r+1)+1) * A.cofactorValue, r, (Matrix<T>) A);
        cofactors.push_back(newCofactor);
    }
    return cofactors;
}

//Sum up the final determinate value from all the
//2x2 cofactors
template <typename T>
T sum_cofactor_dets(std::vector<Cofactor<T> > cofactors)
{
    T sum = 0;
    //Run through all the cofactors
    for(int i = 0; i < (int)cofactors.size(); ++i)
    {
        sum += cofactors[i].cofactorValue * det2_2(cofactors[i]);
    }
    return sum;
}

////////////////////////////////////////////////////////////////////////////////det/////////////////////////////////////////////////////////////////////
template <typename T>
T det(Matrix<T> A)
{
	//if matrix isn't square dont bother
    assert(A._cols == A._rows);

    //If a is just a 2X2
    if(A._matrixVals.size() == 2)
    {
        return det2_2(A);
    }

    //used to store cofactors
    std::vector<Cofactor<T> > oldCofactors(cofactor_matrix(A));
    std::vector<Cofactor<T> > newCofactors;

    //Break down until all the cofactors are 2X2
    while(oldCofactors[0]._rows != 2)
    {
        //Runs through all the cofactors and cofactors them
        for(int i = 0; i < (int)oldCofactors.size(); ++i)
        {
            std::vector<Cofactor<T> > curr_cofac_decomp(cofactor_matrix(oldCofactors[i]));
            //Makes new cofactors out of the current cofactor
            newCofactors.insert(newCofactors.end(), curr_cofac_decomp.begin(), curr_cofac_decomp.end());
        }
        //New cofactors become the old cofactors
        oldCofactors.swap(newCofactors);
        //erases new cofactors
        newCofactors.erase(newCofactors.begin(), newCofactors.end());
    }

    return sum_cofactor_dets(oldCofactors);
}

//////////////Transpose///////////////
template <typename T>
Matrix<T> transpose(Matrix<T> A)
{
    Matrix<T> A_t(A._cols, A._rows);    //Makes the right sized transposed matrix

    for(int i = 0; i < (int) A._matrixVals.size(); ++i)
        for(int j = 0; j < (int)A._matrixVals[0].size(); ++j)
            A_t._matrixVals[j][i] = A._matrixVals[i][j];  //Switch the rows with the cols

    A_t._rows = (int)A_t._matrixVals.size();
    A_t._cols = (int)A_t._matrixVals[0].size();
    A = A_t;    //So the address can be returned properly

    return A;
}

//Print the matrix out all pretty like
template <typename T>
void Matrix<T>::print() const
{
    if(this->_rows == 0 || this->_cols == 0) {std::cout << std::endl << "[Empty Matrix]" << std::endl; return;}

    std::cout << std::endl;
    int longestValue = 2;
    //Find the longest value in matrix and setw according to that
    for(auto r : _matrixVals)
    {
         for(auto c : r)
        {
            std::ostringstream lengCheck;
            if(c > -ZERO_LIMIT && c < ZERO_LIMIT) c = 0;
            lengCheck << c;
            int length = lengCheck.str().size();
            if(length > longestValue) longestValue = length;
        }
    }
    longestValue += 1;

    for(auto r : _matrixVals)
    {
        //if(longestValue > 5) std::cout << std::setprecision(longestValue - 1);
        std::cout << std::setw(longestValue);
        for(auto c : r )
        {
            //Assumes extremely small numbers to be zero
            if(c > -ZERO_LIMIT && c < ZERO_LIMIT) c = 0;

            //prints -0 as 0
            std::ostringstream zeroCheck;
            zeroCheck << c;
            std::string print = zeroCheck.str();
            if(print == "-0") print = "0";
            std::cout << std::setw(longestValue) << print;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
//Returns a pair with the dimensions of the matrix (number of rows,number of columns)
template <typename T>
std::pair<unsigned int, unsigned int> Matrix<T>::size()
{
    return std::make_pair(this->_rows,this->_cols);
}

#endif // MATRIX_H
