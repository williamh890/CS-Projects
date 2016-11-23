#ifndef MATRIX_H
#define MATRIX_H

#include <vector> //vector
#include <iostream> //cout
#include <cassert> //assert
#include <cmath> //abs
#include <utility> //pair, make_pair
#include <iomanip> //setprecision
#include <math.h> //round
#include <type_traits>

template <typename T>
class Matrix
{
    public:
        std::vector<std::vector<T> > matrixVals;
        unsigned int row;
        unsigned int col;
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
        ////////////Elementary Row Ops////////////////
        void replacement(int curRow, int otherRow, T otherRowScale);
        void interchange(int row1, int row2);
        void scale(int row, T scale);
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
    row = (int)matrixVals.size();
    col = (int)matrixVals[0].size();
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
void Matrix<T>::interchange(int row1, int row2)
{
    matrixVals[row1].swap(matrixVals[row2]);
}

template <typename T>
void Matrix<T>::scale(int rowNum, T scale)
{
    assert(rowNum >= 0 &&  rowNum < (int)matrixVals[0].size());

    for(auto & r : matrixVals[rowNum])
    {
        r *= scale;
        //r = ceil(r * pow(10,DECIMAL_PRECISION)) / pow(10,DECIMAL_PRECISION);
    }
}
//replace
template <typename T>
void Matrix<T>::replacement(int curRow, int otherRow, T otherRowScale)  //Current row gets changed
{
    for(int i = 0; i < (int)matrixVals[0].size(); ++i)
    {
        matrixVals[curRow][i] = matrixVals[curRow][i] + (otherRowScale * matrixVals[otherRow][i]);
    }
}

template <typename T>
bool zeroColumn(Matrix<T> A, int currPivotRow, int currPivotCol)
{
    //Assumes zero column
    bool isZeroCol = true;

    for(int r = currPivotRow; r < (int)A.matrixVals.size(); ++r)
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

template <typename T>
void zero_row_to_bottom (Matrix<T> & A, int currPivotRow)
{
    assert(zeroRow(A, currPivotRow));
    //Erase the zero row
    A.matrixVals.erase(A.matrixVals.begin() + currPivotRow);
    //Adds a zero row to the end
    std::vector<T> zeros(A[0].size(), 0);
    A.matrixVals.push_back(zeros);
}

template <typename T>
void move_pivot_to_top(Matrix<T> & A, int currPivotRow, int largestValueRow)
{
    //Moves largest valued row to the top
    A.matrixVals[currPivotRow].swap(A.matrixVals[largestValueRow]);
}

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

template <typename T>
void zero_out_above_and_below(Matrix<T> & A, int currPivotRow, int currPivotCol, int exitRow)
{
    //zero pivot col, except piv position
    for(int r = 0; r < (int)A.matrixVals.size(); ++r)
    {
        //skips zeroing out pivot row, or if value already zero
        if(r == currPivotRow) continue;
        if(A[r][currPivotCol] == 0) continue;

        A.replacement(r, currPivotRow, -A[r][currPivotCol]);
    }
}

template <typename T>
Matrix<T> rref(Matrix<T> A, bool debug = false)
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

    //Starts at the top left of the matrix
    int currPivotCol = 0;
    int currPivotRow = 0;

    //By default exits at the last row
    int exitRow = (int)A.matrixVals.size();

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
Matrix<T>& invert(Matrix<T> A)
{
    //Add identity matrix to the left end of A and row reduce
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
    const int DECIMAL_PRECISION = 3;

    if(this->row == 0 || this->col == 0) {std::cout << std::endl << "[Empty Matrix]" << std::endl; return;}

    std::cout << std::endl;
    for(auto r : matrixVals)
    {
        std::cout << std::setw(DECIMAL_PRECISION);
        for(auto c : r )
        {
            std::cout << std::setw(DECIMAL_PRECISION) << c << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//////////////Transpose///////////////
template <typename T>
Matrix<T> transpose(Matrix<T> A)
{
    Matrix<T> A_t(A.col, A.row);    //Makes the right sized transposed vector

    for(int i = 0; i < A.matrixVals.size(); ++i)
        for(int j = 0; j < A.matrixVals[0].size(); ++j)
            A_t.matrixVals[j][i] = A.matrixVals[i][j];  //Switch the rows with the cols

    A_t.row = (int)A_t.matrixVals.size();
    A_t.col = (int)A_t.matrixVals[0].size();
    A = A_t;    //So the address can be returned properly

    return A;
}

template <typename T>
Matrix<T>::~Matrix()
{
    //dtor
}

#endif // MATRIX_H
