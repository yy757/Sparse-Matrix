//  MATRIX OUTPUT MODULE
//
//  spoutput.hpp
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


#ifndef spoutput_hpp
#define spoutput_hpp

#include <stdio.h>
#include "spdefs.h"

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
void spPrintVector(SparseMatrix Matrix);
/* Matrix pointers are also displayer for debugging */
void spPrintMatrix(SparseMatrix Matrix);

#endif /* spoutput_hpp */
