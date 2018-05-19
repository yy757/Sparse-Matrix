//  MATRIX CREATION MODULE
//
//  spalloc.hpp
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

#ifndef spalloc_hpp
#define spalloc_hpp

#include <stdio.h>
#include "spdefs.h"

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

SparseMatrix spCreate(int Row, int Col, int Nonzero);
SparseMatrix spCreate(double* ValPtr, int* RowPtr, int* ColPtr, int Row, int Col, int Nonzero);

/*
 *  CLEAR MATRIX
 *
 *  Clear all the contents for sparse matrix.
 *
 *  >>> Arguments:
 *  Matrix (Sparse Matrix)
 *
 */
void spClear(SparseMatrix &Matrix);

#endif /* spalloc_hpp */
