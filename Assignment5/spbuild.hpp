//  MATRIX BUILD MODULE
//
//  spbuild.hpp
//  Assignment5
//
//  Created by Leslie Yu on 5/15/18.
//  Copyright © 2018 Leslie Yu. All rights reserved.
//  Description : This file contains the routines associated with initialization, loading and processing the matrix for the sparse matrix routines.

/*
 * >>> User accessible functions :
 *  spAddElement
 *  spGetElement
 *  spReplaceElement
 */

/*
 * IMPORTS
 *
 * >>> Import descriptions:
 * spdefs.hpp
 *      Data structure used for sparse matrix and macros for the sparse matrix routines.
 *
 */

#ifndef spbuild_hpp
#define spbuild_hpp

#include <stdio.h>
#include "spdefs.h"

/*
 *  ADD ELEMENT to the MATRIX ONE BY ONE
 *
 *  Provide the initialization of matrix by adding element one by one
 *  Three conditions to be taken into consideration :
 *      1. The input value is nonzero and the original place is 0
 *      2. The input value is nonzero and the original place is not zero
 *      3. The input value is zero
 *
 *  >>> Arguments:
 *  Matrix (SparseMatrix)
 *      The sparse matrix class defined in spdefs.h
 *  Value (int)
 *      The input value to be added to the matrix
 *  Row (int)
 *      The row length of the matrix
 *  Col (int)
 *      The column length of the matrix
 *
 */
void spAddElement(SparseMatrix &Matrix, double Value, int Row, int Col);

/*
 *  GET ELEMENT to the MATRIX
 *
 *  Provide the access to the matrix element by row index and column index
 *
 *
 *  >>> Arguments:
 *  Matrix (SparseMatrix)
 *      The sparse matrix class defined in spdefs.h
 *
 *  Row (int)
 *      The row length of the matrix
 *  Col (int)
 *      The column length of the matrix
 *
 */
double spGetElement(SparseMatrix &Matrix, int Row, int Col);

#endif /* spbuild_hpp */
