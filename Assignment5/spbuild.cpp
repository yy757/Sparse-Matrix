//  MATRIX BUILD MODULE
//
//  spbuild.cpp
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

#include "spbuild.hpp"

using namespace std;

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

void spAddElement(SparseMatrix &Matrix, double Value, int Row, int Col){
    // Boundary judgement
    if(Row >= Matrix.RowLength || Col >= Matrix.ColLength){
        throw "Cross Boundary!";
    }
    
    /* The input value is nonzero and the original place is 0 */
    if(Value != 0 && spGetElement(Matrix, Row, Col) == 0){
        // assign value to the newly allocated memory space
        double *NewValPtr = new double [Matrix.NonzeroNum];
        int *NewColPtr = new int [Matrix.NonzeroNum];
        for(int i = 0; i < Matrix.NonzeroNum; i++){
            NewValPtr[i] = Matrix.ValPtr[i];
            NewColPtr[i] = Matrix.ColPtr[i];
        }
        
        // release the previous memory space
        Matrix.destructVal();
        Matrix.destructCol();
        
        // reallocate the memory space
        Matrix.NonzeroNum += 1;
        Matrix.ValPtr = new double [Matrix.NonzeroNum];
        Matrix.ColPtr = new int [Matrix.NonzeroNum];

        for(int i = 0; i < Matrix.NonzeroNum - 1; i++){
            Matrix.ValPtr[i] = NewValPtr[i];
            Matrix.ColPtr[i] = NewColPtr[i];
        }
        
        delete [] NewValPtr;
        delete [] NewColPtr;
        
        // move the col array and value array back for one step for the new element
        for(int i = Matrix.NonzeroNum - 1; i >= Matrix.RowPtr[Row]; i--){
            Matrix.ValPtr[i + 1] = Matrix.ValPtr[i];
            Matrix.ColPtr[i + 1] = Matrix.ColPtr[i];
        }
        
        // insert the new element
        Matrix.ValPtr[Matrix.RowPtr[Row]] = Value;
        Matrix.ColPtr[Matrix.RowPtr[Row]] = Col;
        
        // each Matrix.RowPtr value after index i added 1
        for(int i = Row + 1; i <= Matrix.RowLength; i++){
            Matrix.RowPtr[i] ++;
        }
        
        // sort the array range from index [Matrix.RowPtr[Row], Matrix.RowPtr[row+1])
        for(int i = Matrix.RowPtr[Row]; i < Matrix.RowPtr[Row + 1] - 1; i++){
            for(int j = i+1; j < Matrix.RowPtr[Row + 1]; j++){
                if(Matrix.ColPtr[i] > Matrix.ColPtr[j]){
                    int ColTemp = Matrix.ColPtr[i];
                    double ValTemp = Matrix.ValPtr[i];
                    Matrix.ColPtr[i] = Matrix.ColPtr[j];
                    Matrix.ValPtr[i] = Matrix.ValPtr[j];
                    Matrix.ColPtr[j] = ColTemp;
                    Matrix.ValPtr[j] = ValTemp;
                }
            }
        }
    }
    
    /* The input value is nonzero and the original place is not 0 */
    if(Value != 0 && spGetElement(Matrix, Row, Col) != 0){
        // No need to reallocate the memory, just replace the value
        for(int i = Matrix.RowPtr[Row]; i < Matrix.RowPtr[Row + 1]; i++){
            if(Matrix.ColPtr[i] == Col){
                Matrix.ValPtr[i] = Value;
            }
        }
    }
}

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

double spGetElement(SparseMatrix &Matrix, int Row, int Col){
    // Boundary judgement
    if(Row >= Matrix.RowLength || Col >= Matrix.ColLength){
        throw "Cross Boundary!";
    }
    
    // search for the coordinate and get the element
    double Element = 0;
    for(int i = Matrix.RowPtr[Row];i < Matrix.RowPtr[Row + 1]; i++){
        if(Matrix.ColPtr[i] == Col){
            Element = Matrix.ValPtr[i];
        }
    }
    return Element;
}
