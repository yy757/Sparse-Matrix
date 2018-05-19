//  MATRIX UTILITY MODULE
//  sputils.hpp
//  Assignment5
//
//  Created by Leslie Yu on 5/16/18.
//  Copyright © 2018 Leslie Yu. All rights reserved.
//  Description : This file contains various optional utility routines.

/*
 *  >>> User accessible functions contained in this file:
 *  productAx
 *  rowPermute
 *  colPermute
 *  rowScale
 *
 */

/*  IMPORTS
 *
 *  >>> Import descriptions:
 *  spDefs.h
 *      Matrix type and macro definitions for the sparse matrix routines.
 */
#ifndef sputils_hpp
#define sputils_hpp

#include <stdio.h>
#include "spdefs.h"

using namespace std;

/*
 *  PERFORM MATRIX * VECTOR MULTIPLICATION
 *
 *  Provide the computation of Matrix * Vector A * x = b
 *  Conditions:
 *      The length of the input vector has to be consistent with the ColLength of the matrix
 *
 *  >>> Arguments:
 *  Matrix (SparseMatrix)
 *      The sparse matrix class defined in spdefs.h
 *  x (double pointer)
 *      The input vector
 *  Len (int)
 *      The length of the input vector
 *
 *  >>> Return:
 *  b (double pointer)
 *      The output vector
 *
 */
double* spProductAx(SparseMatrix &Matrix, double* x, int Len);

/*
 *  PERFORM ROW PERMUTATION
 *
 *  Provide the function to permute two rows of the matrix
 *  Conditions:
 *      The input i has to be less than input j, no exchange law
 *
 *  >>> Arguments:
 *  Matrix (SparseMatrix)
 *      The sparse matrix class defined in spdefs.h
 *  i (int)
 *      The index of row
 *  j (int)
 *      The index of row
 *
 */
void spRowPermute(SparseMatrix &Matrix, int i, int j);

/*
 *  PERFORM COLUMN PERMUTATION
 *
 *  Provide the function to permute two columns of the matrix
 *
 *  >>> Arguments:
 *  Matrix (SparseMatrix)
 *      The sparse matrix class defined in spdefs.h
 *  i (int)
 *      The index of column
 *  j (int)
 *      The index of column
 *
 */
void spColPermute(SparseMatrix &Matrix, int i, int j);

/*
 *  PERFORM ROW SCALE
 *
 *  Provide the function to scale one row of the matrix by adding anther row * a
 *  Conditions:
 *      a should not be 0
 *
 *  >>> Arguments:
 *  Matrix (SparseMatrix)
 *      The sparse matrix class defined in spdefs.h
 *  i (int)
 *      The index of row to be added
 *  j (int)
 *      The index of row to be scaled
 *  a (double)
 *      The multiplication value
 *
 */
void spRowScale(SparseMatrix &Matrix, int i, int j, double a);

/*
 *  PIVOT FOR MINIMUM FILL IN
 *
 *  Provide the function to find the pivot which has the minimum fill in during Gaussian elimination
 *
 *  >>> Arguments:
 *  Matrix (SparseMatrix)
 *
 *  >>> Return:
 *  pivot (int *)
 *  The row index and column index of the pivot
 *
 */
int* spMinFillinPivot(SparseMatrix &Matrix);

/*
 *  COUNT NONZERO ELEMENT
 *
 *  Provide the function to count the Nonzero element in the current matrix
 *
 *  Explanation : we don't release the space for element turns to 0
 *                which is the rare case in spare matrix transformation
 *
 *  >>> Arguments:
 *  Matrix (SparseMatrix)
 *
 *  >>> Return:
 *  counter (int)
 *  The number of nonzero element of the current matrix
 *
 */
int spCountNonzero(SparseMatrix &Matrix);

/*
 *  CALCULATE THE NORM OF TWO VECTORS
 *
 *  Provide the function to calculate the norm of two vectors to check the matrix solver
 *
 *  Condition : The lengths of the two vectors have to be consistent
 *
 *  >>> Arguments:
 *      a (double *) : vector a
 *      b (double *) : vector b
 *      Lena (int) : length of vector a
 *      Lenb (int) : length of vector b
 *
 *  >>> Return:
 *  norm (double)
 *  The norm of the two vectors
 *
 */
double normVector(double* a, double* b, int Lena, int Lenb);

/*
 *  CALCULATE THE 1-NORM OF MATRIX
 *
 *  Provide the function to calculate the 1-norm of matrix
 *
 *  >>> Arguments:
 *      Matrix (SparseMatrix)
 *
 *  >>> Return:
 *  max (double)
 *  The upperbound of the 1-norm of the matrix
 *
 */
double spNormCol(SparseMatrix &Matrix);

/*
 *  CALCULATE THE INF-NORM OF MATRIX
 *
 *  Provide the function to calculate the inf-norm of matrix
 *
 *  >>> Arguments:
 *      Matrix (SparseMatrix)
 *
 *  >>> Return:
 *  max (double)
 *  The upperbound of the inf-norm of the matrix
 *
 */
double spNormRow(SparseMatrix &Matrix);

/*
 *  CALCULATE THE CONDITION NUMBER OF MATRIX
 *
 *  Provide the function to calculate the condition number of matrix to check the property of the matrix
 *
 *  Condition : Only 1-norm and inf-norm provided
 *
 *  >>> Arguments:
 *      Matrix (SparseMatrix)
 *      NormType (string) : the type of the norm to use : "NormCol" or "NormRow'
 *
 *
 *  >>> Return:
 *  condition (double)
 *  The condition number of the matrix
 *
 */
double spConditionNumber(SparseMatrix &Matrix, string NormType);

/*
 *  CALCULATE THE DIAGONAL MATRIX
 *
 *  Provide the function to calculate the diagonal matrix
 *
 *  >>> Arguments:
 *      Matrix (SparseMatrix)
 *
 *  >>> Return:
 *  Diagonal (Sparse Matrix)
 *  The diagonal matrix of the current matrix
 *
 */
SparseMatrix spGetDiagonal(SparseMatrix &Matrix);

/*
 *  CALCULATE THE INVERSE MATRIX OF THE DIAGONAL MATRIX
 *
 *  Condition : The diagonal element cannot be 0, otherwise will return inf
 *
 *  Provide the function to calculate the inverse matrix of the diagonal matrix
 *
 *  >>> Arguments:
 *      Matrix (SparseMatrix)
 *
 *  >>> Return:
 *  InverseDiagonal (Sparse Matrix)
 *  The inverse diagonal matrix of the current matrix
 *
 */
SparseMatrix spGetInverseDiagonal(SparseMatrix &Matrix);

#endif /* sputils_hpp */
