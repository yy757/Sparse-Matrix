//  MATRIX SOLVE MODULE
//  spsolve.cpp
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

#include "spsolve.hpp"

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
double* spDirectSolver(SparseMatrix &Matrix, double *b, int Len){
    double* x = new double [Matrix.ColLength];

    // copy the matrix for sloving the equation
    SparseMatrix temp = spCreate(Matrix.RowLength,Matrix.ColLength,Matrix.NonzeroNum);
    SparseMatrix B = spCreate(Matrix.RowLength,1,Matrix.RowLength);
    for(int m=0;m<Matrix.RowLength+1;m++){
        temp.RowPtr[m] = Matrix.RowPtr[m];
    }
    for(int m=0;m<Matrix.NonzeroNum;m++){
        temp.ValPtr[m] = Matrix.ValPtr[m];
        temp.ColPtr[m] = Matrix.ColPtr[m];
    }

    for(int m=0;m<Matrix.RowLength;m++){
        spAddElement(B, b[m], m, 0);
    }

//    // get the minimal fill in pivot
//    int* pivot = new int[2];
//    pivot = spMinFillinPivot(temp);
//
//    // switch row and column for both Matrix and Array b
//    spRowPermute(temp, 0, pivot[0]);
//    spColPermute(temp, 0, pivot[1]);
//    spRowPermute(B, 0, pivot[0]);

    // gaussian elimination
    for(int j=0;j<Matrix.ColLength;j++){
        for(int i=j+1;i<Matrix.RowLength;i++){
            double delta = - spGetElement(temp, i, j) / spGetElement(temp, j, j);
            spRowScale(temp, j, i, delta);
            spRowScale(B, j, i, delta);
        }
    }

    // backward substitution
    x[Matrix.ColLength - 1] = spGetElement(B, Matrix.RowLength - 1, 0) / spGetElement(temp, Matrix.RowLength - 1, Matrix.RowLength - 1);
    for(int j=Matrix.ColLength-2;j>=0;j--){
        double product = spGetElement(B, j, 0);
        for(int i=1;i<Matrix.ColLength-j;i++){
            product -= spGetElement(temp, j, j + i) * x[j + i];
        }
        x[j] = product / spGetElement(temp, j, j);
    }
    
//    // column permute
//    double xTemp = x[0];
//    x[0] = x[pivot[1]];
//    x[pivot[1]] = xTemp;

    return x;
}

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
double* spCholeskySolver(SparseMatrix &Matrix, double* b, int Len){
    // create LLo lower triangular matrix and LHi higher triangular matrix
    SparseMatrix LLo = spCreate(Matrix.RowLength, Matrix.ColLength, 0);
    SparseMatrix LHi = spCreate(Matrix.RowLength, Matrix.ColLength, 0);
    
    for(int j = 0; j < Matrix.ColLength; j++){
        for(int i = j; i < Matrix.RowLength; i++){
            
            if(i == j){
                double value = 0;
                for(int k = 0; k < j; k ++){
                    value += spGetElement(LLo, j, k) * spGetElement(LLo, j, k);
                }
                value = sqrt(abs(spGetElement(Matrix, j, j) - value));
                spAddElement(LLo, value, j, j);
                spAddElement(LHi, value, j, j);
            }
            else{
                double value = 0;
                for(int k = 0; k < j; k ++){
                    value += spGetElement(LLo, i, k) * spGetElement(LLo, j, k);
                }
                value = (spGetElement(Matrix, i, j) - value) / spGetElement(LLo, j, j);
                spAddElement(LLo, value, i, j);
                spAddElement(LHi, value, j, i);
            }
        }
    }
    
    // forward substitution LLo * y = b
    double* y = new double[Matrix.ColLength];
    for(int i = 0; i < Matrix.RowLength; i++){
        double value = 0;
        for(int j = 0; j < i; j++){
            value += spGetElement(LLo, i, j) * y[j];
        }
        y[i] = (b[i] - value) / spGetElement(LLo, i, i);
    }
    
    // back substitution LHi * x = y
    double* x = new double [Matrix.ColLength];
    for(int i = Matrix.RowLength-1; i >= 0; i--){
        double value = 0;
        for(int j = Matrix.RowLength-1; j > i; j--){
            value += spGetElement(LHi, i, j) * x[j];
        }
        x[i] = (y[i] - value) / spGetElement(LHi, i, i);
    }
    
    return x;
}

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
double* spJacobiSolver(SparseMatrix &Matrix, double *b, int Len){
    // the solution vector x
    double* x = new double [Matrix.ColLength];
    
    // xNew
    double* xNew = new double [Matrix.ColLength];
    
    // initialize matrix inverse Diagonal matrix
    SparseMatrix InverseDiag = spCreate(Matrix.RowLength, Matrix.ColLength, Matrix.RowLength);
    for(int i=0;i<Matrix.RowLength;i++){
        spAddElement(InverseDiag, 1.0 / spGetElement(Matrix, i, i), i, i);
    }
    
    // initial x with D-1 * b
    x = spProductAx(InverseDiag, b, Len);
    
    // count the loops
    int counter = 0;      
    
    // loop
    while(true){
        
        for(int i=0;i<Matrix.ColLength;i++){
            double sum = 0;
            for(int j=0;j<Matrix.ColLength;j++){
                if(j != i){
                    sum += spGetElement(Matrix, i, j) * x[j];
                }
            }
            xNew[i] = (b[i] - sum) / spGetElement(Matrix, i, i);
        }
        
        // converge criterion
        if(normVector(xNew, x, Matrix.ColLength, Matrix.ColLength) < alpha){
            break;
        }
        
        // maximum loop
        if(counter > MAXLOOP){
            cout<<"The loop didn't converge within " << MAXLOOP << " loops!\n";
            break;
        }
        
        counter ++;
        
        // x(k) = D-1*(L+U)*x(k-1) + D^-1*b
        for(int i=0;i<Matrix.ColLength;i++)
            x[i] = xNew[i];
    }
    
    cout<<"\nHow many iterations took: "<<counter<<endl;
    
    return x;
}

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
double* spSORSolver(SparseMatrix &Matrix, double *b, int Len){
    // define the solution x(k)
    double* x = new double [Matrix.ColLength];
    
    // define the xNew x(k+1)
    double* xNew = new double [Matrix.ColLength];
    
    // initialize matrix D^-1
    SparseMatrix InverseDiag = spCreate(Matrix.RowLength, Matrix.ColLength, Matrix.RowLength);
    for(int i=0;i<Matrix.RowLength;i++){
        spAddElement(InverseDiag, 1.0 / spGetElement(Matrix, i, i), i, i);
    }
    
    // initial x with D-1 * b
    x = spProductAx(InverseDiag, b, Len);
    
    // count loops
    int counter = 0;
    
    // loop
    while(true){
        for(int i=0;i<Matrix.ColLength;i++){
            double sum1 = 0;
            double sum2 = 0;
            for(int j=0;j<Matrix.ColLength;j++){
                if(j<i){
                    sum1 += spGetElement(Matrix, i, j) * xNew[j];
                }
                if(j>i){
                    sum2 += spGetElement(Matrix, i, j) * x[j];
                }
            }
            xNew[i] = (1 - omiga) * x[i] + omiga * (b[i] - sum1 - sum2) / spGetElement(Matrix, i, i);
        }
        
        // converge criterion
        if(normVector(xNew, x, Matrix.ColLength, Matrix.ColLength) < alpha)
            break;
        
        // maximum loop
        if(counter > MAXLOOP){
            cout<<"The loop didn't converge within " << MAXLOOP << " loops!\n";
            break;
        }
        
        counter ++;
        
        // x(k) = x(k-1) + omiga*D^-1*r(k-1);
        for(int i=0;i<Matrix.ColLength;i++)
            x[i] = xNew[i];
    }
    
    cout<<"\nHow many iterations took: "<<counter<<endl;
    
    return x;
}

