/*mymatrix.h*/

// 
// << Nisarg Thakkar >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #02
//

//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>

using namespace std;

template<typename T>
class mymatrix
{
private:
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All 
  // elements are initialized to the default value of T.
  //
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows, 
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");

    Rows = new ROW[R];  // an array with R ROW structs:
    NumRows = R;

    // initialize each row to have C columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[C];  // an array with C elements of type T:
      Rows[r].NumCols = C;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
     }//for loop for row
  }//constructor


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  {
    NumRows = other.NumRows;  
	Rows = new ROW[NumRows];  // an array with ROW structs = other (created) matrix's num of rows
    
    
    for (int r = 0; r < NumRows; ++r)
    {
        Rows[r].NumCols = other.Rows[r].NumCols; //copying attributes of other(orginial) matrix to new one
        Rows[r].Cols = new T[Rows[r].NumCols];  // an array with number elements of type T equals to other matrix's num cols:
      
      //copying element from other to new one
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = other.Rows[r].Cols[c];  // default value for type T:
      }
     }//for loop 
    
  }


  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {
    return NumRows;
  }
  

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::numcols: row");

    return Rows[r].NumCols; //returning number of columns for specified row
  }


  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int C)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");
    if (C <= Rows[r].NumCols)
        return;

    if (C > Rows[r].NumCols)    //only grow it if wanted columns are bigger than orginial matrix's columns
    { 
        T* newRow = new T[C];  //grow row to have C columns, assinging nw pointer to have a bigger size of C
        
        for (int i = 0; i < Rows[r].NumCols; i++)
        {
            newRow[i] = Rows[r].Cols[i];  //copying column elements from old pointer to new allocated memory (bigger)
        }
        for (int i = Rows[r].NumCols; i < C; i++)
        {
            newRow[i] = T{};  //putting by default values in grown column
        }
        
        delete[] Rows[r].Cols;  //deleting old array since it is already copied
        
        Rows[r].Cols = newRow;  //asssigning old pointer to new one
        Rows[r].NumCols = C;  
   }
  }

  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  // 
  void grow(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::grow: # of cols");

    if (R < NumRows) //if input row for new matrix is smaller than original matrix, R becomes num of rows in originial matrix, we never shrink
      R = NumRows;
    
    mymatrix<T> grown(R, C);        //making a new matrix of s specified size
        
    for (int i = 0; i < NumRows; i++) //if old matrix has columns greater than new one, then go to those rows and call growcols
    {
      if (Rows[i].NumCols > C)
        grown.growcols(i, Rows[i].NumCols); //increasing number columns for specific rows
    }
    
    //going to each element and copying from original 
    for (int i = 0; i < NumRows; i++)
    {
      for (int j = 0; j < Rows[i].NumCols; j++)
      {
        if (j < Rows[i].NumCols)
          grown.Rows[i].Cols[j] = Rows[i].Cols[j];
      }   
        delete[] Rows[i].Cols; //deleting cols pointer after done copying
     } 
      delete[] Rows; //deleteing ROW array pointer
     
      Rows = grown.Rows; //asssigning those pointers to new created grown matrix
      NumRows = grown.NumRows; //chainging the num rows to reflect the growth of matrix
        
        for (int i = 0; i < R; i++)
        {
            Rows[i].Cols = grown.Rows[i].Cols; //assigning Rows[i].Cols pointer newly created matrix
            Rows[i].NumCols = grown.Rows[i].NumCols; //changing col sizes
        }   
  }


  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const
  {
    int count = 0;
    for (int i = 0; i < NumRows; i++) //goes to each ROW structure
    {
      for (int j = 0; j < Rows[i].NumCols; j++) //counts column numbers in that row
      { 
        count++;
      }
    }
    return count;    
  }


  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //return by reference
  T& at(int r, int c)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");

    return Rows[r].Cols[c]; 
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //return by reference
  T& operator()(int r, int c)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");

    return Rows[r].Cols[c];
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar)
  {
    mymatrix<T> result(NumRows, 1);    //creating a new matrix of NumRows *  1 size, then will call growcols function for specific rows

    for (int i = 0; i < NumRows; i++) //goes to each ROW structure
    {
      result.growcols(i, Rows[i].NumCols); //increasing number of columns
      for (int j = 0; j < Rows[i].NumCols; j++) //counts column numbers in that row
      { 
        result.Rows[i].Cols[j] = Rows[i].Cols[j] * scalar; //multiplies old elements and stores in new result matrix
      }
    }
    return result;
  }


  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  bool recCheck() const //checking if both matrix are rectangle
  {
    int firstNumCol = Rows[0].NumCols, count = 0;
    
    for (int i = 0; i < NumRows; i++)
    {
      if (Rows[i].NumCols == firstNumCol) //cheking if all rows have same columns, if it's true return true
        count++;
    }
    
    if (count == NumRows) 
      return true;
    return false;
  }
  
  
  
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    mymatrix<T> result(NumRows, other.Rows[0].NumCols); //creating new matrix of NumRows * NumCOls size (all cols have same size, rectangle)
    bool thisRec, otherRec;

    //
    // both matrices must be rectangular for this to work:
    //
    thisRec = this->recCheck(); //checked if both matrix are rectangle
    otherRec = other.recCheck();
    
    
    if (!thisRec)
      throw runtime_error("mymatrix::*: this not rectangular");
    //
    if (!otherRec)
      throw runtime_error("mymatrix::*: other not rectangular");

    //
    // Okay, both matrices are rectangular.  Can we multiply?  Only
    // if M1 is R1xN and M2 is NxC2.  This yields a result that is
    // R1xC2.
    // 
    // Example: 3x4 * 4x2 => 3x2
  
    if (Rows[0].NumCols != other.NumRows) //making size of matrix is appropriate to perfrom multiplication
       throw runtime_error("mymatrix::*: size mismatch");

    //
    // Okay, we can multiply:
  
    int sum = 0;
    for (int i = 0; i < result.NumRows; i++)
    {
        for(int j = 0; j < result.Rows[0].NumCols; j++)
        {
            for(int p = 0; p < Rows[0].NumCols; p++)
            {
                sum += Rows[i].Cols[p] * other.Rows[p].Cols[j];  //performing matrix multiplication and using two outer for loops to
            }                                                    // put result in the right place
            result(i,j) = sum;
            sum = 0;
        }
    }

    return result;
  }


  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};
