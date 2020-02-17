/*Nisarg Thakkar
Project 2, CS 251
nthakk28@uic.edu

mymatrix implementation and testing */

#include <iostream>
#include <string>
#include "mymatrix.h"

using namespace std;

int main()
{
    mymatrix<int> M1, M2, M3, M4, M5; //default constructor checking
    M1._output();
    cout << "recCheck: " << M1.recCheck() << endl; //checking rectangle cheking funtion
    
    M1.growcols(0,7); //checking grow column function
    cout << M1.size() << endl; //cheking size function
    cout << endl;
    
    M4(0,1) = 3;
    M1.at(0,0) = 1; //putting values in M1 and M2, by cheking at function and () operator overloading
    M1(0,1) = 4;
    M2(1,1) = 3;
    M1.grow(6,4); //cheking all different combination of grow function 
    //M.grow(4, 6);
    //M.grow(3,6);
    //M.grow(3, 3);
    //M.grow(3,4);
    //M.grow(4,4);
    //
    //M.grow(4,3);
    //M.grow(6,3);
    //M.grow(6,6);
    M5 = M1 * 2; //checking scalar multiplication
    
    //Matrix Multiplication
    //M3 = M1 * M2 // throwing the correct error! this(M1 is not rectangle)
    M3 = M4 * M2; //checking matrix multiplication
    
    M1._output();
    M2._output();
    M3._output();
    cout << "recCheck" << M4.recCheck() << endl;
    
    mymatrix<char> C1;
    C1._output(); //checking for blank, and print empty char
    C1(1,1) = 'b';
    C1._output(); //can see b
    C1 = C1 * 2;
    C1._output(); //printing question mark, since ascii value is not defined for that
    
    mymatrix<double> D1, D2, D3;
    D1._output(); //checking for zeros ad its double type
    D1(1,1) = 5.7;
    D1._output(); //can see 5.7 at (1,1)
    D1 = D1 * 2;  //scalar multiplication
    D1._output(); 
    D2(1,1) = 2.5;  
    D3 = D1 * D2;  //checking for matrix multiplication
    D3._output();
    
}  
