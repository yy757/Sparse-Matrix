//  MATRIX CREATION MODULE
//
//  spalloc.cpp
//  Assignment5
//
//  Created by Leslie Yu on 5/15/18.
//  Copyright © 2018 Leslie Yu. All rights reserved.
//  Description : This file contains the creation and memory allocations for sparse matrix

/*
 * >>> User accessible functions :
 *  spCreate
 *
 */

/*
 * IMPORTS
 *
 * >>> Import descriptions:
 * spdefs.hpp
 *      Data structure used for sparse matrix and macros for the sparse matrix routines.
 *
 */

#include "spalloc.hpp"

using namespace std;

/*
 *  CREATE MATRIX
 *
 *  Creation and memory allocation for sparse matrix.
 *  Provide two possible ways for the creation of matrix:
 *      1. create matrix without element pointer
 *      2. create matrix with known element pointer
 *
 *  >>> Arguments:
 *  Row (int)
 *      The row length of the matrix
 *  Col (int)
 *      The column length of the matrix
 *  Nonzero (int)
 *      The number of nonzero elements in the matrix
 *
 *  ValPtr (double)
 *      The pointer to the element of the matrix
 *  RowPtr (int)
 *      The pointer to the row index of the matrix
 *  ColPtr (int)
 *      The pointer to the column index of the matrix
 *
 */

/* create matrix without element pointer */
SparseMatrix spCreate(int Row, int Col, int Nonzero){
    SparseMatrix Matrix;
    
    Matrix.RowLength = Row;
    Matrix.ColLength = Col;
    Matrix.NonzeroNum = Nonzero;
    Matrix.RowPtr = new int[Matrix.RowLength+1];
    Matrix.ColPtr = new int[Matrix.NonzeroNum];
    Matrix.ValPtr = new double[Matrix.NonzeroNum];
    fill(Matrix.RowPtr, Matrix.RowPtr + Matrix.RowLength + 1, 0.0);
    fill(Matrix.ColPtr, Matrix.ColPtr + Matrix.NonzeroNum, 0.0);
    fill(Matrix.ValPtr, Matrix.ValPtr + Matrix.NonzeroNum, 0.0);
    
    return Matrix;
}

/* create matrix with known element pointer */
SparseMatrix spCreate(double* ValPtr, int* RowPtr, int* ColPtr, int Row, int Col, int Nonzero){
    SparseMatrix Matrix;
    
    // initialize parameters
    Matrix.NonzeroNum = Nonzero;
    Matrix.RowLength = Row;
    Matrix.ColLength = Col;
    
    // assign address of array to Ptr
    Matrix.ValPtr = ValPtr;
    Matrix.RowPtr = RowPtr;
    Matrix.ColPtr = ColPtr;
    
    return Matrix;
}

/*
 *  CLEAR MATRIX
 *
 *  Clear all the contents for sparse matrix.
 *
 *  >>> Arguments:
 *  Matrix (Sparse Matrix)
 *
 */
void spClear(SparseMatrix &Matrix){
    fill(Matrix.ValPtr, Matrix.ValPtr + Matrix.NonzeroNum, 0.0);
    fill(Matrix.RowPtr, Matrix.RowPtr + Matrix.RowLength + 1, 0.0);
    fill(Matrix.ColPtr, Matrix.ColPtr + Matrix.NonzeroNum, 0.0);
}
