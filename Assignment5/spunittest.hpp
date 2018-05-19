//  SPARSE MATRIX TEST MODULE
//  spunittest.hpp
//  Assignment5
//
//  Created by Leslie Yu on 5/16/18.
//  Copyright © 2018 Leslie Yu. All rights reserved.
//  Description : This file contains all tests for Sparse matrix. Unit testing, white box testing, black box testing, Wilkinson principle used.

/*
 * IMPORTS
 *
 * >>> Import descriptions:
 * spdefs.hpp
 *      Data structure used for sparse matrix and macros for the sparse matrix routines.
 * memusage.hpp
 *      Memory usage monitor
 *
 */

#ifndef spunittest_hpp
#define spunittest_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include "spdefs.h"
#include "memusage.hpp"

using namespace std;

/* test for Sparse Matrix Creation */
/*
 *  Testing method :
 *      Compared to ground truth
 */
void testCreate();

/* test for Sparse Matrix Build */
/*
 *  Testing method :
 *      Compared to ground truth
 */
void testBuild();

/* test for Sparse Matrix utilities */
/*
 *  Testing method :
 *      Compared to ground truth
 */
void testUtility();

/* test for Direct Solver */
/*
 *>>> Condition :
 *      1. For the Cholesky Decomposition, the matrix has to be symmetric, positive definite matrix
 *      but doesn't has to be diagonal dominant, which means does not have to be a small condition number
 *      2. For the Gaussian elimination, the matrix must be well-conditioned, which has a small condition number
 *      Usually, we make it diagonal dominant.
 *
 *>>> Paramaters :
 *      1. Matrix : Sparse Matrix  <input>
 *      2. b : Input right hand side  <input>
 *      3. RHS : Calculated right hand side  <output>
 *      4. norm : norm of the vector b and RHS  <output>
 *
 *  Testing method :
 *      Compared to ground truth
 */
void testIterativeSolver();

/* test for Large Scale Matrix */
/*  ground truth :
 *      No ground truth
 *>>> Input file :
 *         bcsstm20.mtx
 
 *>>> Condition :
 *      1. For the Cholesky Decomposition, the matrix has to be symmetric, positive definite matrix
 *      but doesn't has to be diagonal dominant, which means does not have to be a small condition number
 *      2. For the Gaussian elimination, the matrix must be well-conditioned, which has a small condition number
 *      Usually, we make it diagonal dominant.
 *
 *>>> Paramaters :
 *      1. Matrix : Sparse Matrix  <input>
 *      2. b : Input right hand side  <input>  b = [1,1,1,1,...,1]
 *      3. RHS : Calculated right hand side  <output>
 *      4. norm : norm of the vector b and RHS  <output>
 *      5. condition : the condition number of the matrix <output>
 *      6. if symmetric : close to 0 means symmetric while large number means asymmetric <output>
 *      7. sum of matrix : check the sum of all elements in the matrix to ensure the correctness
 *      close 0 means right while large number means wrong.
 *  Testing method :
 *      Use backward substitution
 */
void testLargeScaleMatrix(string method);

#endif /* spunittest_hpp */
