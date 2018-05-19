//  DATA STRUCTURE AND MACRO DEFINITIONS for Sparse
//  spdefs.h
//  Assignment5
//
//  Created by Leslie Yu on 5/15/18.
//  Copyright © 2018 Leslie Yu. All rights reserved.
//  Description : This file contains data structure used for sparse matrix and macros for the sparse matrix routines. The definitions are of no use to the users.



#ifndef spdefs_h
#define spdefs_h
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

class SparseMatrix{
public:
    int RowLength;
    int ColLength;
    int NonzeroNum;
    double *ValPtr;
    int *RowPtr;
    int *ColPtr;
    
    void destructVal(){
        delete []ValPtr;
    }
    void destructRow(){
        delete []RowPtr;
    }
    void destructCol(){
        delete []ColPtr;
    }
    ~ SparseMatrix(){
    }
};

#endif /* spdefs_h */

/* solver macros */
#define alpha 0.0000001
#define MAXLOOP 1000
#define omiga 0.5
/* output form macros */
#define width_5 5
#define width_10 10
#define width_15 15
#define width_20 20
#define width_25 25
#define width_30 30

/* functions declaration */
// spalloc
extern SparseMatrix spCreate(int Row, int Col, int Nonzero);
extern SparseMatrix spCreate(double* ValPtr, int* RowPtr, int* ColPtr, int Row, int Col, int Nonzero);
extern void spClear(SparseMatrix &Matrix);

// spbuild
extern void spAddElement(SparseMatrix &Matrix, double Value, int Row, int Col);
extern double spGetElement(SparseMatrix &Matrix, int Row, int Col);

// spoutput
extern void spPrintVector(SparseMatrix Matrix);
extern void spPrintMatrix(SparseMatrix Matrix);

// sputils
extern double* spProductAx(SparseMatrix &Matrix, double* x, int Len);
extern void spRowPermute(SparseMatrix &Matrix, int i, int j);
extern void spColPermute(SparseMatrix &Matrix, int i, int j);
extern void spRowScale(SparseMatrix &Matrix, int i, int j, double a);
extern int spCountNonzero(SparseMatrix &Matrix);
extern int* spMinFillinPivot(SparseMatrix &Matrix);
extern double normVector(double* a, double* b, int Lena, int Lenb);
extern SparseMatrix spGetDiagonal(SparseMatrix &Matrix);
extern SparseMatrix spGetInverseDiagonal(SparseMatrix &Matrix);
extern double spNormCol(SparseMatrix &Matrix);
extern double spNormRow(SparseMatrix &Matrix);
double spConditionNumber(SparseMatrix &Matrix, string NormType);

// spsolve
extern double* spDirectSolver(SparseMatrix &Matrix, double *b, int Len);
extern double* spCholeskySolver(SparseMatrix &Matrix, double* b, int Len);
extern double* spJacobiSolver(SparseMatrix &Matrix, double *b, int Len);
extern double* spSORSolver(SparseMatrix &Matrix, double *b, int Len);

