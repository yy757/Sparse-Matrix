//  SPARSE MATRIX TEST MODULE
//  spunittest.cpp
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

#include "spunittest.hpp"
#define LARGEMATRIXPATH "/Users/leslieyu/Desktop/ECE4960/Assignment5/bcsstm20/bcsstm20.mtx"
#define rowPath "/Users/leslieyu/Desktop/ECE4960/Assignment5/rowPtr.csv"
#define colPath "/Users/leslieyu/Desktop/ECE4960/Assignment5/colInd.csv"
#define valuePath "/Users/leslieyu/Desktop/ECE4960/Assignment5/value.csv"

/* test for Sparse Matrix Creation */
/*
 *  Testing method :
 *      Compared to ground truth
 */
void testCreate(){
    /* test for spCreate without element pointer */
    cout << "test for spCreate without element pointer" << endl;
    /* ground truth : 3 * 3 matrix
     *  0  0  0
     *  0  0  0
     *  0  0  0
     *
     *  matrix pointer:
     *  ValPtr:
     *  RowPtr: 0 0 0 0
     *  ColPtr:
     */
    SparseMatrix Matrix1 = spCreate(3, 3, 0);
    spPrintMatrix(Matrix1);
    spPrintVector(Matrix1);
    
    /* test for spCreate with element pointer */
    cout << "test for spCreate with element pointer" << endl;
    /* ground truth : 3 * 3 matrix
     *  1         0         0
     *  0         2         0
     *  0         0         3
     *
     *  matrix pointer:
     *  ValPtr: 1 2 3
     *  RowPtr: 0 1 2 3
     *  ColPtr: 0 1 2
     */
    double *Value = new double [3];
    Value[0] = 1;
    Value[1] = 2;
    Value[2] = 3;
    int *Row = new int [4];
    Row[0] = 0;
    Row[1] = 1;
    Row[2] = 2;
    Row[3] = 3;
    int *Col = new int [3];
    Col[0] = 0;
    Col[1] = 1;
    Col[2] = 2;
    SparseMatrix Matrix2 = spCreate(Value, Row, Col, 3, 3, 3);
    spPrintMatrix(Matrix2);
    spPrintVector(Matrix2);
    
    /* test for spClear function */
    cout << "test for spClear function" << endl;
    /* ground truth : 3 * 3 matrix
     *
     *  0         0         0
     *  0         0         0
     *  0         0         0
     *
     *
     */
    spClear(Matrix2);
    spPrintMatrix(Matrix2);
}

/* test for Sparse Matrix Build */
/*
 *  Testing method :
 *      Compared to ground truth
 */
void testBuild(){
    /* test for spAddElement function */
    cout << "test for spAddElement function" << endl;
    double *Value = new double [3];
    Value[0] = 1;
    Value[1] = 2;
    Value[2] = 3;
    int *Row = new int [4];
    Row[0] = 0;
    Row[1] = 1;
    Row[2] = 2;
    Row[3] = 3;
    int *Col = new int [3];
    Col[0] = 0;
    Col[1] = 1;
    Col[2] = 2;
    SparseMatrix Matrix = spCreate(Value, Row, Col, 3, 3, 3);
    
    // case 1 : The input value is nonzero and the original place is 0
    /* ground truth : 3 * 3 matrix
     *  1         0         0
     *  0         2         2
     *  0         0         3
     *
     *  matrix pointer:
     *  ValPtr: 1 2 2 3
     *  RowPtr: 0 1 3 4
     *  ColPtr: 0 1 2 2
     */
    spAddElement(Matrix, 2, 1, 2);
    spPrintMatrix(Matrix);
    
    // case 2 : The input value is nonzero and the original place is not zero
    /* ground truth : 3 * 3 matrix
     *  1         0         0
     *  0         2         2
     *  0         0         6
     *
     *  matrix pointer:
     *  ValPtr: 1 2 2 6
     *  RowPtr: 0 1 3 4
     *  ColPtr: 0 1 2 2
     */
    spAddElement(Matrix, 6, 2, 2);
    spPrintMatrix(Matrix);
    
    /* test for spGetElement function */
    cout << "test for spGetElement function" << endl;
    /* ground truth :
     *      Matrix[2][2] = 6
     *
     */
    cout << "Matrix[2][2] = ";
    cout << spGetElement(Matrix, 2, 2) << endl;
}

/* test for Sparse Matrix utilities */
/*
 *  Testing method :
 *      Compared to ground truth
 */
void testUtility(){
    /* test for spProductAx function */
    cout << "test for spProductAx function" << endl;
    /* ground truth :
     *      b[0] = 0
     *      b[1] = 4
     *      b[2] = 15
     */
    SparseMatrix A = spCreate(3, 3, 0);
    
    spAddElement(A, 2, 1, 1);
    spAddElement(A, 6, 2, 1);
    spAddElement(A, 1, 2, 2);
    
    double x[3] = {1,2,3};
    double *b = spProductAx(A, x, 3);
    for(int i = 0; i < 3; i ++){
        cout << "b[" << i << "] = ";
        cout << b[i] << endl;
    }
    
    /* test for spRowPermute function */
    cout << "test for spRowPermute function" << endl;
    /* ground truth :
     *      0         0         0
     *      0         6         1
     *      0         2         0
     *
     *      ValPtr: 6 1 2
     *      RowPtr: 0 0 2 3
     *      ColPtr: 1 2 1
     */
    spRowPermute(A, 1, 2);
    spPrintMatrix(A);
    spPrintVector(A);
    
    /* test for spColPermute function */
    cout << "test for spColPermute function" << endl;
    /* ground truth :
     *      0         0         0
     *      6         0         1
     *      2         0         0
     *
     *      ValPtr: 6 1 2
     *      RowPtr: 0 0 2 3
     *      ColPtr: 0 2 0
     */
    spColPermute(A, 0, 1);
    spPrintMatrix(A);
    spPrintVector(A);
    
    /* test for spRowScale function */
    cout << "test for spRowScale function" << endl;
    /* ground truth :
     *      0         0         0
     *      6         0         1
     *      23        0         3.5
     *
     *      ValPtr: 6 1 23 3.5
     *      RowPtr: 0 0 2 4
     *      ColPtr: 0 2 0 2
     */
    spRowScale(A, 1, 2, 3.5);
    spPrintMatrix(A);
    spPrintVector(A);
    
    /* test for spMinFillinPivot function */
    cout << "test for spMinFillinPivot function" << endl;
    /* ground truth :
     *      0         1         2
     *      3         2         0
     *      0         3         0
     *
     *      x = 2
     *      y = 1
     *
     *      3         0         0
     *      2         3         0
     *      1         0         2
     * >>>
     *      3         0         0
     *      0         3         0
     *      0         0         2
     */
    spClear(A);
    spAddElement(A, 1, 0, 1);
    spAddElement(A, 2, 0, 2);
    spAddElement(A, 3, 1, 0);
    spAddElement(A, 2, 1, 1);
    spAddElement(A, 3, 2, 1);
    spPrintMatrix(A);
    int* pivot = spMinFillinPivot(A);
    cout << "x = " << pivot[0];
    cout << "y = " << pivot[1];
    
    /* test for spCountNonzero function */
    cout << "test for spCountNonzero function" << endl;
    /* ground truth :
     *      0         1         2
     *      3         2         0
     *      0         3         0
     *
     *  Number of Nonzero = 5
     */
    cout << "Number of Nonzero = " << spCountNonzero(A);
    
    /* test for normVector function" */
    cout << "test for normVector function" << endl;
    /* ground truth :
     * case 1:
     *  a :
     *      4   7   6
     *  b :
     *      4   7   6
     *  norm :
     *      0
     *
     * case 2:
     *  a :
     *      2.5   7   6
     *  b :
     *      4   7.5  6
     *  norm :
     *      1.58
     */
    
    // case 1
    double* a = new double [3];
    a[0] = 4;
    a[1] = 7;
    a[2] = 6;
    delete [] b;
    b = new double [3];
    b[0] = 4;
    b[1] = 7;
    b[2] = 6;
    cout << "norm of case 1 : " << normVector(a, b, 3, 3) << endl;
    
    // case 2
    a[0] = 2.5;
    a[1] = 7;
    a[2] = 6;
    b[0] = 4;
    b[1] = 7.5;
    b[2] = 6;
    cout << "norm of case 2 : " << normVector(a, b, 3, 3) << endl;
    
    /* test for spNormCol and spNormRow function" */
    cout << "test for spNormCol and spNormRow function" << endl;
    /* ground truth :
     * case 1:
     *  40        12        -15
     *  12        37        -20
     *  -16       -43       49
     *
     *  NormCol : 92
     *  NormRow : 108
     */
    double *Value = new double [9];
    Value[0] = 40;
    Value[1] = 12;
    Value[2] = -15;
    Value[3] = 12;
    Value[4] = 37;
    Value[5] = -20;
    Value[6] = -16;
    Value[7] = -43;
    Value[8] = 49;
    int *Row = new int [4];
    Row[0] = 0;
    Row[1] = 3;
    Row[2] = 6;
    Row[3] = 9;
    int *Col = new int [9];
    Col[0] = 0;
    Col[1] = 1;
    Col[2] = 2;
    Col[3] = 0;
    Col[4] = 1;
    Col[5] = 2;
    Col[6] = 0;
    Col[7] = 1;
    Col[8] = 2;
    A.~SparseMatrix();
    A = spCreate(Value, Row, Col, 3, 3, 9);
    spPrintMatrix(A);
    cout << "NormCol : " << spNormCol(A) << endl;
    cout << "NormRow : " << spNormRow(A) << endl;
    
    /* test for spConditionNumber function" */
    cout << "test for spConditionNumber function" << endl;
    /* ground truth :
     *  case 1:
     *  40        12        -15
     *  12        37        -20
     *  -16       -43       49
     *
     *  Condition Number (NormType = NormCol) = 2.48649
     *  Condition Number (NormType = NormRow) = 2.91892
     *
     *  case 2:
     *  0.003     59.14
     *  5.291     -6.13 
     *
     *  Condition Number (NormType = NormCol) = 21756.7
     *  Condition Number (NormType = NormRow) = inf
     */
    cout << "condition  (NormType = NormCol): " << spConditionNumber(A, "NormCol");
    cout << "condition  (NormType = NormRow): " << spConditionNumber(A, "NormRow");
    SparseMatrix B = spCreate(2, 2, 0);
    spAddElement(B, 0.003, 0, 0);
    spAddElement(B, 59.14, 0, 1);
    spAddElement(B, 5.291, 1, 0);
    spAddElement(B, 6.13, 1, 1);
    spPrintMatrix(B);
    cout << "condition  (NormType = NormCol): " << spConditionNumber(B, "NormCol");
    cout << "condition  (NormType = NormRow): " << spConditionNumber(B, "NormRow");
}

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

void testDirectSolver(){
    /* test for spDirectSolver function */
    /* ground truth :
     *  A:
     *      0         1         2
     *      3         2         0
     *      0         3         0
     *
     * case 1:
     *  b:
     *      4         7         6
     *
     *  x:
     *      1         2         1
     *
     * case 2:
     *  b:
     *      5         7         6
     *
     *  x:
     *      1         2         1.5
     */
    cout << "test for spDirectSolver function" << endl;
    SparseMatrix A = spCreate(3, 3, 0);
    spAddElement(A, 1, 0, 1);
    spAddElement(A, 2, 0, 2);
    spAddElement(A, 3, 1, 0);
    spAddElement(A, 2, 1, 1);
    spAddElement(A, 3, 2, 1);
    
    // case 1
    double* b = new double [3];
    b[0] = 4;
    b[1] = 7;
    b[2] = 6;
    
    double* x = spDirectSolver(A, b, 3);
    
    for(int i = 0; i < 3; i ++){
        cout << "x[" << i << "] = ";
        cout << x[i] << endl;
    }
    
    double* RHS = spProductAx(A, x, 3);
    
    for(int i = 0; i < 3; i ++){
        cout << "RHS[" << i << "] = ";
        cout << RHS[i] << endl;
    }
    
    // case 2
    b[0] = 5;
    b[1] = 7;
    b[2] = 6;
    
    x = spDirectSolver(A, b, 3);
    
    for(int i = 0; i < 3; i ++){
        cout << "x[" << i << "] = ";
        cout << x[i] << endl;
    }
    
    RHS = spProductAx(A, x, 3);
    
    for(int i = 0; i < 3; i ++){
        cout << "RHS[" << i << "] = ";
        cout << RHS[i] << endl;
    }
    
    /* test for spCholeskySolver function */
    /* ground truth :
     *  A:
     *      4         12        -16
     *      12        37        -43
     *      -16       -43       98
     *
     * case 1:
     *  b:
     *      -26        -58.5       233
     *
     *  x:
     *      1.5         2         3.5
     */
    cout << "test for spCholeskySolver function" << endl;
    double *Value = new double [9];
    Value[0] = 4;
    Value[1] = 12;
    Value[2] = -16;
    Value[3] = 12;
    Value[4] = 37;
    Value[5] = -43;
    Value[6] = -16;
    Value[7] = -43;
    Value[8] = 98;
    int *Row = new int [4];
    Row[0] = 0;
    Row[1] = 3;
    Row[2] = 6;
    Row[3] = 9;
    int *Col = new int [9];
    Col[0] = 0;
    Col[1] = 1;
    Col[2] = 2;
    Col[3] = 0;
    Col[4] = 1;
    Col[5] = 2;
    Col[6] = 0;
    Col[7] = 1;
    Col[8] = 2;
    
    A.~SparseMatrix();
    A = spCreate(Value, Row, Col, 3, 3, 9);
    spPrintMatrix(A);
    b[0] = -26;
    b[1] = -58.5;
    b[2] = 233;
    x = spCholeskySolver(A, b, 3);
    
    for(int i = 0; i < 3; i ++){
        cout << "x[" << i << "] = ";
        cout << x[i] << endl;
    }
    
    RHS = spProductAx(A, x, 3);
    
    for(int i = 0; i < 3; i ++){
        cout << "RHS[" << i << "] = ";
        cout << RHS[i] << endl;
    }
    
}

/* test for Iterative Solver */
/*
 *>>> Condition :
 *      The tested matrix is diagonal dominant
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

void testIterativeSolver(){
    /* test for spJacobiSolver function */
    /* ground truth :
     *  A:
     *      40                  12               -16
     *      12                  37               -43
     *      -16                 -43               98
     *
     * case 1:
     *  b:
     *      -26     -58.5       233
     *
     *  x:
     *       0.000843711       2.4117              3.43588
     *
     */
    cout << "test for spJacobiSolver function" << endl;
    double *Value = new double [9];
    Value[0] = 40;
    Value[1] = 12;
    Value[2] = -16;
    Value[3] = 12;
    Value[4] = 37;
    Value[5] = -43;
    Value[6] = -16;
    Value[7] = -43;
    Value[8] = 98;
    int *Row = new int [4];
    Row[0] = 0;
    Row[1] = 3;
    Row[2] = 6;
    Row[3] = 9;
    int *Col = new int [9];
    Col[0] = 0;
    Col[1] = 1;
    Col[2] = 2;
    Col[3] = 0;
    Col[4] = 1;
    Col[5] = 2;
    Col[6] = 0;
    Col[7] = 1;
    Col[8] = 2;
    SparseMatrix A = spCreate(Value, Row, Col, 3, 3, 9);
    spPrintMatrix(A);
    double* b = new double [3];
    b[0] = -26;
    b[1] = -58.5;
    b[2] = 233;
    double* x = spJacobiSolver(A, b, 3);
    
    for(int i = 0; i < 3; i ++){
        cout << "x[" << i << "] = ";
        cout << x[i] << endl;
    }
    
    double* RHS = spProductAx(A, x, 3);
    
    for(int i = 0; i < 3; i ++){
        cout << "RHS[" << i << "] = ";
        cout << RHS[i] << endl;
    }
    
    cout << "norm(b, RHS) : " << normVector(b, RHS, 3, 3) << endl;
    
    /* test for spSORSolver function */
    /* ground truth :
     *  A:
     *      40                  12               -16
     *      12                  37               -43
     *      -16                 -43               98
     *
     * case 1:
     *  b:
     *      -26     -58.5       233
     *
     *  x:
     *       0.000843711       2.4117              3.43588
     *
     */
    cout << "test for spSORSolver function" << endl;
    x = spSORSolver(A, b, 3);
    
    for(int i = 0; i < 3; i ++){
        cout << "x[" << i << "] = ";
        cout << x[i] << endl;
    }
    
    RHS = spProductAx(A, x, 3);
    
    for(int i = 0; i < 3; i ++){
        cout << "RHS[" << i << "] = ";
        cout << RHS[i] << endl;
    }
    
    cout << "norm(b, RHS) : " << normVector(b, RHS, 3, 3) << endl;
}

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

void testLargeScaleMatrix(string method){
    
/*********************** Direct Solver Test *********************/
    if(method == "Iterative"){
        // define parameters
        int M = 5000;
        int N = 5000;
        int L = 253677;

        // starttime;
        clock_t starttime;
        starttime = clock();

        // Open the test file:
        ifstream RowIn(rowPath);
        ifstream ColIn(colPath);
        ifstream ValIn(valuePath);

        // read data into a one-dimension array
        double* ValPtr = new double [L];
        for(int i = 0; i < L; i++){
            ValIn >> ValPtr[i];
        }


        // read rowPtr into a one-dimension array
        int* RowPtr = new int [M+1];
        for(int i = 0; i < M+1; i++){
            RowIn >> RowPtr[i];
            RowPtr[i] --;
        }

        // read colPtr into a one-dimension array
        int* ColPtr = new int [L];
        for(int i = 0; i < L; i++){
            ColIn >> ColPtr[i];
            ColPtr[i] --;
        }

        // create matrix
        SparseMatrix Matrix = spCreate(ValPtr, RowPtr, ColPtr, M, N, L);

        // close file
        RowIn.close();
        ColIn.close();
        ValIn.close();
        cout<<"Load data successfully!"<<endl;
        cout<<"Time elapsed: "<<(clock()-starttime)/double(CLOCKS_PER_SEC)<<endl;

        /***  Test b1 = (1,0,0,...,0) ***/
        cout<<"Test Jacobi Method "<<endl;
        // reset start time
        starttime = clock();

        // initialize b
        double* b = new double [M];
        fill(b, b + M, 0.0);
        b[0] = 1.0;

        // define solution x
        double* x = new double [N];
        x = spJacobiSolver(Matrix, b, M);

        cout<<"Solution has been found! "<<endl;
        cout<<"Time elapsed: "<<(clock()-starttime)/double(CLOCKS_PER_SEC) << " s" <<endl;

        memUsage();

        // validation
        double *RHS = new double [M];
        RHS = spProductAx(Matrix, x, N);
        // second norm of b1 and RHS
        double norm = normVector(RHS, b, M, M);
        cout<<"second norm of RHS and b: "<<norm<<endl;
        
        /***  Test b1 = (1,0,0,...,0) ***/
        cout<<"Test SOR Method "<<endl;
        // reset start time
        starttime = clock();
        
        // solution x
        x = spSORSolver(Matrix, b, M);
        
        cout<<"Solution has been found! "<<endl;
        cout<<"Time elapsed: "<<(clock()-starttime)/double(CLOCKS_PER_SEC) << " s" <<endl;
        
        memUsage();
        
        // validation
        RHS = spProductAx(Matrix, x, N);
        // second norm of b1 and RHS
        norm = normVector(RHS, b, M, M);
        cout<<"second norm of RHS and b: "<<norm<<endl;
    }
    
/*********************** Direct Solver Test *********************/
    if(method == "Direct"){
        // Open the file:
        ifstream fin(LARGEMATRIXPATH);
        
        // Ignore headers and comments:
        while (fin.peek() == '%') fin.ignore(2048, '\n');
        
        // Read defining parameters:
        int M, N, L;
        fin >> M >> N >> L;
        
        // Initiate the object with M, N, L
        SparseMatrix Matrix = spCreate(M, N, L);
        
        double sum=0;
        
        // Read the data
        for (int l = 0; l < L; l++)
        {
            int m, n;
            double data;
            fin >> m >> n >> data;
            spAddElement(Matrix, data, m-1, n-1);
            sum += data;
        }
        
        // close file
        fin.close();
        
        // compare the sum of all the elements of the matrix to ensure the correctness
        double *x = new double [N];
        fill(x, x + N, 1.0);
        
        double *RHS = spProductAx(Matrix, x, N);
        for(int i = 0; i < M; i ++){
            sum -= RHS[i];
        }
        
        cout << "check sum of the matrix :" << sum << endl;
        
        // construct the right hand side to solve the equation
        double *b = new double [M];
        fill(b, b + N, 1.0);
        b[0] = 1;
        
        // Test Cholesky method
        cout << "Cholesky Method" << endl;
        
        // set starttime
        clock_t starttime;
        starttime = clock();
        
        // make diagonal dominant
        for(int i = 0; i < M; i ++){
            spAddElement(Matrix, 15, i, i);
        }
        
        cout << "Condition number : " << spConditionNumber(Matrix, "NormRow") << endl;
        
        // check the symmetry of the matrix
        double checksum = 0;
        for(int i = 0; i < M; i ++){
            for(int j = 0; j < N; j++){
                checksum += spGetElement(Matrix, i, j) - spGetElement(Matrix, j, i);
            }
        }
        
        cout << "if not symmetric :" << checksum << endl;
        x = spCholeskySolver(Matrix, b, M);
        
        memUsage();
        cout<<"Solution has been found! "<<endl;
        cout<<"Time elapsed: "<<(clock()-starttime)/double(CLOCKS_PER_SEC) << " s" <<endl;
        // validation
        RHS = spProductAx(Matrix, x, N);
        // second norm of b1 and RHS
        double norm = normVector(RHS, b, M, M);
        cout<<"second norm of RHS and b: "<<norm<<endl;
        
        // Test Gaussian elimination method
        cout << "Gaussian Elimination Method" << endl;
        
        // set starttime
        starttime = clock();
        x = spDirectSolver(Matrix, b, M);
        
        cout << "Condition number : " << spConditionNumber(Matrix, "NormRow") << endl;
        
        memUsage();
        cout<<"Solution has been found! "<<endl;
        cout<<"Time elapsed: "<<(clock()-starttime)/double(CLOCKS_PER_SEC) << " s" <<endl;
        
        // validation
        RHS = spProductAx(Matrix, x, N);
        // second norm of b1 and RHS
        norm = normVector(RHS, b, M, M);
        cout<<"second norm of RHS and b: "<<norm<<endl;
    }
}
