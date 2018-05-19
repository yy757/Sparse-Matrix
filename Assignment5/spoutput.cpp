//  MATRIX OUTPUT MODULE
//
//  spoutput.cpp
//  Assignment5
//
//  Created by Leslie Yu on 5/15/18.
//  Copyright © 2018 Leslie Yu. All rights reserved.
//  Description : This file contains the output-to-file and output-toscreen routines for the matrix package

/*
 * >>> User accessible functions :
 *  spPrintVector
 *  spPrintMatrix
 */

/*
 * IMPORTS
 *
 * >>> Import descriptions:
 * spdefs.hpp
 *      Data structure used for sparse matrix and macros for the sparse matrix routines.
 * spbuild.hpp
 *      Routines associated with initialization, loading and processing the matrix for the sparse matrix
 *      routines.
 */

#include "spoutput.hpp"

using namespace std;

/*
 *  PRINT MATRIX
 *
 *  Formats and send the matrix to standard output.
 *  Some elementary statistics are also output.
 *  Provide two display format of the matrix:
 *      1. Full matrix is displayed for the users.
 *      2. Matrix pointers are also displayer for debugging
 *
 *  >>> Arguments:
 *  Matrix  <input>  (char *)
 *      Pointer to matrix.
 *
 *
 *  >>> Local variables:
 *  width (int)
 *      manipulate the output form by the macros defined in spdefs.h
 */

/* Full matrix is displayed for the users */
void spPrintVector(SparseMatrix Matrix){
    cout << "\ndisplay as Matrix Pointer";
    cout << "\nValPtr:";
    for(int i = 0; i < Matrix.NonzeroNum; i++)
        cout << " " << Matrix.ValPtr[i];
    cout << "\nRowPtr:";
    for(int i = 0; i < Matrix.RowLength + 1; i++)
        cout << " " << Matrix.RowPtr[i];
    cout << "\nColPtr:";
    for(int i = 0; i < Matrix.NonzeroNum; i++)
        cout << " " << Matrix.ColPtr[i];
    cout << endl;
}

/* Matrix pointers are also displayer for debugging */
void spPrintMatrix(SparseMatrix Matrix){
    cout << "\ndisplay as Full Matrix\n";
    for(int i = 0; i < Matrix.RowLength; i++){
        for(int j = 0; j < Matrix.ColLength; j++){
            cout << left << setw(width_10);
            cout << spGetElement(Matrix, i, j);
        }
        cout<<endl;
    }
    cout<<endl;
}
