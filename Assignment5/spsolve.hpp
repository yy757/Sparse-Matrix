//  MATRIX SOLVE MODULE
//  spsolve.hpp
//  Assignment5
//
//  Created by Leslie Yu on 5/16/18.
//  Copyright © 2018 Leslie Yu. All rights reserved.
//  Description : This file contains the direct solver and iterative solver for the sparse matrix

/*
 *
 *  >>> User accessible functions contained in this file:
 *  spDirectSolver
 *  spCholeskySolver
 *  spJacobiSolver
 *  spSORSolver
 *
 */

/*
 *  IMPORTS
 *
 *  >>> Import descriptions:
 *  spdefs.h
 *     Matrix type and macro definitions for the sparse matrix routines.
 */
#ifndef spsolve_hpp
#define spsolve_hpp

#include <stdio.h>
#include "spdefs.h"

/*
 *  DIRECT SOLVER OF SPARSE MATRIX
 *
 *  Performs forward elimination and back substitution to find the
 *  unknown vector from the RHS vector and factored matrix.  This
 *  routine uses the pivot which has minimum fill in.
 *
 *  Condition : The length of the input vector b has to be consistent with Matrix.Collength
 *
 *  >>> Arguments:
 *  Matrix  (Sparse Matrix)
 *
 *  b  (double *)
 *      b is the input data array, the right hand side.
 *  Len (int)
 *      The length of the input vector b
 *  >>> Return:
 *  x  (double *)
 *      Solution is the output data array.
 *
 */
double* spDirectSolver(SparseMatrix &Matrix, double *b, int Len);

/*
 *  DIRECT SOLVER OF SPARSE MATRIX
 *
 *  Performs the cholesky decomposition to decomposes the matrix into
 *  the product of a lower triangular matrix and its conjugate transpose.
 *  Then do forward substitution and backward substitution to compute the unkown vector
 *
 *  Condition : The input matrix has to be Hermitian positive-definite matrix
 *
 *  >>> Arguments:
 *  Matrix  (Sparse Matrix)
 *
 *  b  (double *)
 *      b is the input data array, the right hand side.
 *  Len (int)
 *      The length of the input vector b
 *  >>> Return:
 *  x  (double *)
 *      Solution is the output data array.
 *
 */
double* spCholeskySolver(SparseMatrix &Matrix, double* b, int Len);
/*
 *  ITERATIVE SOLVER OF SPARSE MATRIX
 *
 *  The Jacobi method is an algorithm for determining the solutions
 *  of a diagonally dominant system of linear equations. Each diagonal element is solved for
 *  and an approximate value is plugged in. The process is then iterated until it converges.
 *
 *  Condition : The input matrix has to be diagonal dominant
 *
 *  >>> Arguments:
 *  Matrix  (Sparse Matrix)
 *
 *  b  (double *)
 *      b is the input data array, the right hand side.
 *  Len (int)
 *      The length of the input vector b
 *  >>> Return:
 *  x  (double *)
 *      Solution is the output data array.
 *
 */
double* spJacobiSolver(SparseMatrix &Matrix, double *b, int Len);

/*
 *  ITERATIVE SOLVER OF SPARSE MATRIX
 *
 *  The method of successive over-relaxation (SOR) is a variant of the Gauss–Seidel method
 *  for solving a linear system of equations, resulting in faster convergence.
 *  A similar method can be used for any slowly converging iterative process.
 *
 *  Condition : The input matrix has to be diagonal dominant
 *
 *  >>> Arguments:
 *  Matrix  (Sparse Matrix)
 *
 *  b  (double *)
 *      b is the input data array, the right hand side.
 *  Len (int)
 *      The length of the input vector b
 *  >>> Return:
 *  x  (double *)
 *      Solution is the output data array.
 *
 */
double* spSORSolver(SparseMatrix &Matrix, double *b, int Len);
#endif /* spsolve_hpp */
