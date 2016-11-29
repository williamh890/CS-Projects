#ifndef MATRIX_H
#define MATRIX_H

#include <vector> //vector
#include <iostream> //cout
#include <cassert> //assert
#include <cmath> //abs, round
#include <utility> //pair, make_pair
#include <iomanip> //setprecision
#include <sstream> //ostringstream
#include <string> //string


template <typename T>
class Matrix
{
    public:
        std::vector<std::vector<T> > _matrixVals;
        unsigned int _rows; //Number of rows
        unsigned int _cols; //Number of columns
        ////////////////CTORS//////////////
        //Defaults to a
        Matrix(int r = 1, int c = 1, T val = 0);
        Matrix(std::vector<std::vector<T> > data);

        virtual ~Matrix() = default; //DTOR
        //////////////Operations/////////////
        std::vector<T> operator[](size_t i);
        Matrix& operator+=(const Matrix & b);
        Matrix& operator-=(const Matrix & b);
        Matrix& operator*=(T scalar);
        Matrix<T>& operator*=(Matrix<T> & B);

        ///////////////////Utility//////////////////
        void resize(int newRowSize, int newColSize, T fillvalue = 0);
        void subMatrix(std::pair<int,int> topLeft,std::pair<int,int> botRight);
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
        ////////////////Display/////////////////
        void print() const;

};
///////////////////////CTORS/////////////////////////
template <typename T>
Matrix<T>::Matrix(int r, int c, T val) :  _rows(r), _cols(c)
{
    _matrixVals.resize(r);
    for(int i = 0; i < (int)_matrixVals.size(); ++i)
    {
        _matrixVals[i].resize(c, val);
    }
    _rows = (int)_matrixVals.size();
    _cols = (int)_matrixVals[0].size();
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T> > data) : _matrixVals(data)
{
    _rows = (int)_matrixVals.size();
    _cols = (int)_matrixVals[0].size();
}
/////////////////////////////////////////////////////////////


/////////////////////////////OPERATORS////////////////////////
template <typename T>
std::vector<T> Matrix<T>::operator[](size_t i)  //Indexing
{
    return _matrixVals[i];
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix & b)  //Addition
{
    for(int r = 0; r < this->_rows; ++r)
    {
        for(int c = 0; c < this->_cols; ++c)
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
    for(int r = 0; r < this->_rows; ++r)
    {
        for(int c = 0; c < this->_cols; ++c)
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
    for(int r = 0; r < this->_rows; ++r)
    {
        for(int c = 0; c < this->_cols; ++c)
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
Matrix<T>& Matrix<T>::operator*=(Matrix<T> & B) //Matrix Multiplication
{
    assert(this->_cols == B._rows);
    //Matrix multiplication A*B
    Matrix<T> multResult(this->_rows,B._cols,0);

    std::cout << this->_rows << " " << B._cols << std::endl;

    T slot;
    for(int r = 0; r < multResult._rows; ++r)
    {
        slot = 0;
        for(int c = 0; c < multResult._cols; ++c)
        {
            slot = 0;
            for(int i = 0; i < B._rows; ++i)
            {
                std::cout << B._rows << std::endl;
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

///////////////////////////FUCNTIONALITY///////////////////////////

//Resize a matrix by adding rows/cols full of an indicated value
template <typename T>
void Matrix<T>::resize(int newNumRows, int newNumCols, T fillValue)
{
    //std::vector<std::vector<T> > data

    if(newNumCols > this->_cols)
    {
        //Add new values (zero by default) to the end of all row vectors
        for(auto & r : this->_matrixVals)
        {
            r.insert(r.end(), (newNumCols - this->_cols), fillValue);
        }
    }
    if(newNumCols < this->_cols)
    {
        //Remove appropriate number of ending rows
        //Erase the ending values
        for(auto & r: this->_matrixVals)
        {
            r.resize(newNumCols);
        }
    }
    if(newNumRows > this->_rows)
    {
        //Makes new rows and fills them with a desired value
        std::vector<T> newRows(newNumCols, fillValue);
        this->_matrixVals.insert(_matrixVals.end(), (newNumRows - this->_rows), newRows);
    }
    if(newNumRows < this->_rows)
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
template <typename T>
void Matrix<T>::subMatrix(std::pair<int,int> topLeft, std::pair<int,int> botRight)
{
    //Makes sure that the coords are really top left and top right
    assert(topLeft.first <= botRight.first);
    assert(topLeft.second <= botRight.second);

    //Gets ride of rows


}

////////////////Adding cols///////////////
template <typename T>
void Matrix<T>::addCol(std::vector<T> col)
{
    assert(col.size() == _matrixVals.size());
    for(int i = 0; i < _matrixVals.size(); ++i)
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

        if(A._matrixVals[currRow][currCol] != 1) return false;
        for(int r = currRow - 1; r >= 0; --r)
        {
            if(A._matrixVals[r][currCol] != 0) return false;
        }
    }
    return true;
}

template <typename T>
void Matrix<T>::interchange(int row1, int row2)
{
    _matrixVals[row1].swap(_matrixVals[row2]);
}

template <typename T>
void Matrix<T>::scale(int rowNum, T scale)
{
    assert(rowNum >= 0 &&  rowNum < (int)_matrixVals[0].size());

    for(auto & r : _matrixVals[rowNum])
    {
        r *= scale;
        //r = ceil(r * pow(10,DECIMAL_PRECISION)) / pow(10,DECIMAL_PRECISION);
    }
}
//replace
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

    for(int r = currPivotRow; r < (int)A._matrixVals.size(); ++r)
    {
        //If a value is not zero, then break
        if(A[r][currPivotCol] != 0)
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

    for(int c = 0; c < (int)A[0].size(); ++c)
    {
        if(A[currPivotRow][c] != 0)
        {
            isZeroRow = false;
            break;
        }
    }
    return isZeroRow;
}
//Gives the position of the largest value in that column
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

    //rowScale = ceil(rowScale * pow(10,DECIMAL_PRECISION)) / pow(10,DECIMAL_PRECISION);

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
        if(A[r][currPivotCol] == 0) continue;

        A.replacement(r, currPivotRow, -A[r][currPivotCol]);
    }
}
/////////////////ROW REDUCED ECHELON FORM//////////////////
template <typename T>
Matrix<T> rref(Matrix<T> A, bool debug = false)
{
    //Starts at the top left of the matrix
    int currPivotCol = 0;
    int currPivotRow = 0;

    //By default exits at the last row
    int exitRow = (int)A._matrixVals.size();

    bool isDone = false;

    if(debug) A.print();

    while(currPivotRow != exitRow)
    {
        while(true)
        {
            //If row of zeros, move to the bottom and add 1 to the exit row
            if(zeroRow(A,currPivotRow))
            {
                zero_row_to_bottom(A, currPivotRow);
                --exitRow;
            }
            //Makes sure the next row isnt also a zero row
            if(!zeroRow(A,currPivotRow)) break;
            //Checks to see if done
            if(currPivotRow >= exitRow)
            {
                isDone = true;
                break;
            }
        }
        if(isDone) break;

        if(debug) A.print();

        //If all zeros in pivot position
        while(true)
        {
            if(zeroColumn(A,currPivotRow,currPivotCol)) ++currPivotCol;
            else break;
        }
        //finds the largest value in the pivot column
        int largestValueRow = largest_value_position(A,currPivotRow,currPivotCol, exitRow); //Returns the row that has the largest value

        if(debug) std::cout << "LVR: " << largestValueRow << std::endl;
        if(debug) std::cout << "PR: " << currPivotRow << " " << "PC: " << currPivotCol << std::endl;

        //Move the largest value row to the top
        move_pivot_to_top(A, currPivotRow, largestValueRow);

        if(debug) A.print();

        scale_pivot_row_to_1(A, currPivotRow, currPivotCol);

        if(debug) A.print();

        zero_out_above_and_below(A, currPivotRow, currPivotCol, exitRow);
        ++currPivotRow;
    }
    return A;
}
/////////////////////////////////
template <typename T>
void add_id(Matrix<T> & A)
{
    //Creates vector of zeros
    std::vector<T> id_Row(A[0].size(), 0);
    //Loops through all the rows
    for(int r = 0, id_c = 0; r < A._matrixVals.size(); ++r, ++id_c)
    {
        //Puts a one in the vec
        id_Row[id_c] = 1;
        //Tacks it onto the end of the matrix
        A._matrixVals[r].insert(A._matrixVals[r].end(), id_Row.begin(), id_Row.end());
        //Sets the vector back to zero
        id_Row.assign(id_Row.size(), 0);
    }
}

template <typename T>
void remove_id(Matrix<T> & A)
{
    for(int r = 0; r < A._matrixVals.size(); ++r)
    {
        A._matrixVals[r].erase(A._matrixVals[r].begin(), A._matrixVals[r].begin() + (A[r].size()/2));
    }
}

template <typename T>
Matrix<T> invert(Matrix<T> A)
{
    add_id(A);
    A = rref(A);
    remove_id(A);
    return A;
}

template <typename T>
T det2_2(Matrix<T> A)
{
    return ((A[0][0] * A[1][1]) - (A[0][1] * A[1][0]));
}

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

//////////Determinant////////////
template <typename T>
T det(Matrix<T> A){
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
    while(true)
    {
        //all cofactor matrices are 2x2
        if(oldCofactors[0]._rows == 2) break;

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

template <typename T>
void Matrix<T>::print() const
{
    const int DECIMAL_PRECISION = 3;

    if(this->_rows == 0 || this->_cols == 0) {std::cout << std::endl << "[Empty Matrix]" << std::endl; return;}

    std::cout << std::endl;
    for(auto r : _matrixVals)
    {
        std::cout << std::setw(DECIMAL_PRECISION);
        for(auto c : r )
        {
            if(c > -1e-10 && c < 1e-10)
            {
                c = 0;
            }
            //fix for -0
            std::ostringstream zeroCheck;
            zeroCheck << c;
            std::string print = zeroCheck.str();
            if(print == "-0") print = "0";

            std::cout << std::setw(DECIMAL_PRECISION) << print << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//////////////Transpose///////////////
template <typename T>
Matrix<T> transpose(Matrix<T> A)
{
    Matrix<T> A_t(A._cols, A._rows);    //Makes the right sized transposed vector

    for(int i = 0; i < A._matrixVals.size(); ++i)
        for(int j = 0; j < A._matrixVals[0].size(); ++j)
            A_t._matrixVals[j][i] = A._matrixVals[i][j];  //Switch the rows with the cols

    A_t._rows = (int)A_t._matrixVals.size();
    A_t._cols = (int)A_t._matrixVals[0].size();
    A = A_t;    //So the address can be returned properly

    return A;
}


#endif // MATRIX_H
