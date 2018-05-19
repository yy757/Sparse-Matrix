//  MATRIX UTILITY MODULE
//  sputils.cpp
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
#include "sputils.hpp"

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
double* spProductAx(SparseMatrix &Matrix, double* x, int Len){
    if(Len == Matrix.ColLength){
        double* b = new double[Matrix.RowLength];
        for(int i = 0; i < Matrix.RowLength; i++){
            b[i] = 0;
        }
        for(int i = 0; i < Matrix.RowLength; i++){
            for(int j = Matrix.RowPtr[i]; j < Matrix.RowPtr[i + 1]; j++){
                b[i] += Matrix.ValPtr[j] * x[Matrix.ColPtr[j]];
            }
        }
    
        return b;
    }
    
    else{
        throw "The length of the input array is not consistent with the matrix!";
    }
}

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
void spRowPermute(SparseMatrix &Matrix, int i, int j){
    // boundary check
    if(i >= Matrix.RowLength || j >= Matrix.RowLength){
        throw "Out of boundary!";
    }
    
    // i needs to be less than j
    if(i >= j){
        cout << "i needs to be less than j!" << endl;
    }
    
    // i needs to be less than j
    if(i < j){
        int delta = (Matrix.RowPtr[j + 1] - Matrix.RowPtr[j]) - (Matrix.RowPtr[i + 1] - Matrix.RowPtr[i]);
        if(delta >= 0){
            // new array to store Matrix.RowPtr[i + 1]-Matrix.RowPtr[i]
            double* vali = new double[Matrix.RowPtr[i + 1] - Matrix.RowPtr[i]];
            double* coli = new double[Matrix.RowPtr[i + 1] - Matrix.RowPtr[i]];
            // store Matrix.RowPtr[i + 1]-Matrix.RowPtr[i] value
            int index = 0;
            for(int m=Matrix.RowPtr[i];m<Matrix.RowPtr[i + 1];m++){
                vali[index] = Matrix.ValPtr[m];
                coli[index] = Matrix.ColPtr[m];
                index++;
            }
            
            // new array to store Matrix.RowPtr[j + 1]-Matrix.RowPtr[j]
            double* valj = new double[Matrix.RowPtr[j + 1]-Matrix.RowPtr[j]];
            double* colj = new double[Matrix.RowPtr[j + 1]-Matrix.RowPtr[j]];
            // store Matrix.RowPtr[j + 1]-Matrix.RowPtr[j] value
            index = 0;
            for(int m=Matrix.RowPtr[j];m<Matrix.RowPtr[j + 1];m++){
                valj[index] = Matrix.ValPtr[m];
                colj[index] = Matrix.ColPtr[m];
                index++;
            }
            
            // permute the elements between Matrix.RowPtr[i + 1] and Matrix.RowPtr[j]
            for(int m=Matrix.RowPtr[j]-1;m>=Matrix.RowPtr[i + 1];m--){
                Matrix.ValPtr[m+delta] = Matrix.ValPtr[m];
                Matrix.ColPtr[m+delta] = Matrix.ColPtr[m];
            }
            
            // put Matrix.RowPtr[j] into Matrix.RowPtr[i]
            index = 0;
            for(int m=Matrix.RowPtr[i];m<Matrix.RowPtr[i + 1]+delta;m++){
                Matrix.ValPtr[m] = valj[index];
                Matrix.ColPtr[m] = colj[index];
                index++;
            }
            
            // put Matrix.RowPtr[i] into Matrix.RowPtr[j]
            index = 0;
            for(int m=Matrix.RowPtr[j]+delta;m<Matrix.RowPtr[j + 1];m++){
                Matrix.ValPtr[m] = vali[index];
                Matrix.ColPtr[m] = coli[index];
                index++;
            }
            delete []vali;
            delete []coli;
            delete []valj;
            delete []colj;
        }
        
        if(delta<0){
            // new array to store Matrix.RowPtr[i + 1]-Matrix.RowPtr[i]
            double* vali = new double[Matrix.RowPtr[i + 1]-Matrix.RowPtr[i]];
            double* coli = new double[Matrix.RowPtr[i + 1]-Matrix.RowPtr[i]];
            // store Matrix.RowPtr[i + 1]-Matrix.RowPtr[i] value
            int index = 0;
            for(int m=Matrix.RowPtr[i];m<Matrix.RowPtr[i + 1];m++){
                vali[index] = Matrix.ValPtr[m];
                coli[index] = Matrix.ColPtr[m];
                index++;
            }
            
            // new array to store Matrix.RowPtr[j + 1]-Matrix.RowPtr[j]
            double* valj = new double[Matrix.RowPtr[j + 1]-Matrix.RowPtr[j]];
            double* colj = new double[Matrix.RowPtr[j + 1]-Matrix.RowPtr[j]];
            // store Matrix.RowPtr[j + 1]-Matrix.RowPtr[j] value
            index = 0;
            for(int m=Matrix.RowPtr[j];m<Matrix.RowPtr[j + 1];m++){
                valj[index] = Matrix.ValPtr[m];
                colj[index] = Matrix.ColPtr[m];
                index++;
            }
            
            // permute the elements between Matrix.RowPtr[i + 1] and Matrix.RowPtr[j]
            for(int m=Matrix.RowPtr[i + 1];m<Matrix.RowPtr[j];m++){
                Matrix.ValPtr[m+delta] = Matrix.ValPtr[m];
                Matrix.ColPtr[m+delta] = Matrix.ColPtr[m];
            }
            
            // put Matrix.RowPtr[j] into Matrix.RowPtr[i]
            index = 0;
            for(int m=Matrix.RowPtr[i];m<Matrix.RowPtr[i + 1]+delta;m++){
                Matrix.ValPtr[m] = valj[index];
                Matrix.ColPtr[m] = colj[index];
                index++;
            }
            
            // put Matrix.RowPtr[i] into Matrix.RowPtr[j]
            index = 0;
            for(int m=Matrix.RowPtr[j]+delta;m<Matrix.RowPtr[j + 1];m++){
                Matrix.ValPtr[m] = vali[index];
                Matrix.ColPtr[m] = coli[index];
                index++;
            }
            delete []vali;
            delete []coli;
            delete []valj;
            delete []colj;
        }
        
        for(int m = i + 1; m < j + 1; m++)                // change Matrix.RowPtr
            Matrix.RowPtr[m]+=delta;
    }
}

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
void spColPermute(SparseMatrix &Matrix, int i, int j){
    // boundary check
    if(i >= Matrix.ColLength || j >= Matrix.ColLength){
        throw "Out of boundary!";
    }
    
    for(int m=1;m<Matrix.RowLength+1;m++){
        int flagi = 0;
        int flagj = 0;
        int indexi = 0;
        int indexj = 0;
        
        // determine whether value[i] value[j] is zero
        for(int n=Matrix.RowPtr[m-1];n<Matrix.RowPtr[m];n++){
            if(Matrix.ColPtr[n] == i){
                flagi = 1;
                indexi = n;
            }
            if(Matrix.ColPtr[n] == j){
                flagj = 1;
                indexj = n;
            }
        }
        
        // both of i and j are nonzero
        if(flagi && flagj){
            double temp = Matrix.ValPtr[indexi];
            Matrix.ValPtr[indexi] = Matrix.ValPtr[indexj];
            Matrix.ValPtr[indexj] = temp;
        }
        
        // if i is zero and j is nonzero
        if(!flagi && flagj){
            Matrix.ColPtr[indexj] = i;
        }
        
        // if j is zero and i is nonzero
        if(flagi && !flagj){
            Matrix.ColPtr[indexi] = j;
        }
    }
}

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
void spRowScale(SparseMatrix &Matrix, int i, int j, double a){
    // boundary check
    if(i >= Matrix.RowLength || j >= Matrix.RowLength){
        throw "Out of boundary!";
    }
    
    if(a != 0){
        // count the newly nonzero number
        int counter = 0;
        for(int m=Matrix.RowPtr[i];m<Matrix.RowPtr[i + 1];m++){
            for(int n=Matrix.RowPtr[j];n<Matrix.RowPtr[j + 1];n++){
                if(Matrix.ColPtr[m] == Matrix.ColPtr[n]){
                    counter++;
                }
            }
        }
        
        int delta = Matrix.RowPtr[i + 1]-Matrix.RowPtr[i]-counter;
        
        double* newvalPtr = new double[Matrix.NonzeroNum+delta];          // construct new value pointer
        int* newcolPtr = new int[Matrix.NonzeroNum+delta];          // construct new column pointer
        for(int m=0;m<Matrix.NonzeroNum;m++){
            newcolPtr[m] = Matrix.ColPtr[m];
            newvalPtr[m] = Matrix.ValPtr[m];
        }
        
        // permute the new array
        for(int m=Matrix.NonzeroNum-1;m>=Matrix.RowPtr[j + 1];m--){
            newcolPtr[m+delta] = newcolPtr[m];
            newvalPtr[m+delta] = newvalPtr[m];
        }
        
        // input the new data
        int offset=0;
        for(int m=Matrix.RowPtr[i];m<Matrix.RowPtr[i + 1];m++){
            int flag = 0;
            int index = 0;
            for(int n=Matrix.RowPtr[j];n<Matrix.RowPtr[j + 1];n++){
                if(Matrix.ColPtr[m] == Matrix.ColPtr[n]){
                    flag = 1;
                    index = n;
                }
            }
            if(flag == 0){
                newcolPtr[Matrix.RowPtr[j]+offset]=Matrix.ColPtr[m];
                newvalPtr[Matrix.RowPtr[j]+offset]=Matrix.ValPtr[m]*a;
                offset++;
            }
            if(flag == 1){
                newvalPtr[Matrix.RowPtr[j]+offset] = Matrix.ValPtr[index]+Matrix.ValPtr[m]*a;
                newcolPtr[Matrix.RowPtr[j]+offset] = Matrix.ColPtr[m];
                offset++;
            }
        }
        
        for(int n=Matrix.RowPtr[j];n<Matrix.RowPtr[j + 1];n++){
            int flag = 0;
            for(int m=Matrix.RowPtr[i];m<Matrix.RowPtr[i + 1];m++){
                if(Matrix.ColPtr[m] == Matrix.ColPtr[n]){
                    flag = 1;
                }
            }
            if(flag == 0){
                newcolPtr[Matrix.RowPtr[j]+offset]=Matrix.ColPtr[n];
                newvalPtr[Matrix.RowPtr[j]+offset]=Matrix.ValPtr[n];
                offset++;
            }
        }
        
        // sort the newvalPtr and newcolPtr in range (Matrix.RowPtr[j],Matrix.RowPtr[j + 1]+delta) excluded
        for(int m=Matrix.RowPtr[j];m<Matrix.RowPtr[j + 1]+delta;m++){
            for(int n=m+1;n<Matrix.RowPtr[j + 1]+delta;n++){
                if(newcolPtr[m]>newcolPtr[n]){
                    int coltemp=newcolPtr[m];
                    double valtemp=newvalPtr[m];
                    newcolPtr[m] = newcolPtr[n];
                    newvalPtr[m] = newvalPtr[n];
                    newcolPtr[n] = coltemp;
                    newvalPtr[n] = valtemp;
                }
            }
        }
        
        // changes to the Matrix.RowPtr  !!!!! This has to be done at last, because all Matrix.ValPtr and Matrix.ColPtr are connected with it. Once it is changed, it all changed.
        for(int m=j+1;m<Matrix.RowLength+1;m++){
            Matrix.RowPtr[m] += delta;
        }
        
        delete [] Matrix.ValPtr;
        delete [] Matrix.ColPtr;
        
        Matrix.ValPtr = newvalPtr;       //assign the new initial address to Matrix.ValPtr
        Matrix.ColPtr = newcolPtr;      //assign the new initial address to Matrix.ColPtr
        Matrix.NonzeroNum += delta;
    }
}

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
int* spMinFillinPivot(SparseMatrix &Matrix){
    int* pivot = new int [2];
    int min = Matrix.RowLength * Matrix.ColLength;
    for(int x_axis=0;x_axis<Matrix.RowLength;x_axis++){
        for(int y_axis=0;y_axis<Matrix.ColLength;y_axis++){
            if(spGetElement(Matrix, x_axis, y_axis) != 0){
                // define and initialize a new matrix
                SparseMatrix temp = spCreate(Matrix.RowLength,Matrix.ColLength,Matrix.NonzeroNum);
                for(int m=0;m<Matrix.RowLength+1;m++)
                    temp.RowPtr[m] = Matrix.RowPtr[m];
                for(int m=0;m<Matrix.NonzeroNum;m++){
                    temp.ValPtr[m] = Matrix.ValPtr[m];
                    temp.ColPtr[m] = Matrix.ColPtr[m];
                }
                
                // switch the pivot to [1,1]
                spRowPermute(temp, 0, x_axis);
                spColPermute(temp, 0, y_axis);
    
                // gaussian elimination
                for(int j=0;j<Matrix.ColLength;j++){
                    for(int i=j+1;i<Matrix.RowLength;i++){
                        // -temp.matrix[i][j]/temp.matrix[j][j]
                        double delta = - spGetElement(temp, i, j) / spGetElement(temp, j, j);
                        spRowScale(temp, j, i, delta);
                    }
                }
                
                // find the minimum
                if(spCountNonzero(temp)<min){
                    pivot[0] = x_axis;
                    pivot[1] = y_axis;
                    min = spCountNonzero(temp);
                }
            }
        }
    }
    return pivot;
}

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
int spCountNonzero(SparseMatrix &Matrix){
    int counter = 0;
    for(int i = 0; i < Matrix.NonzeroNum; i++){
        if(Matrix.ValPtr[i]!=0){
            counter ++;
        }
    }
    return counter;
}

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
double normVector(double* a, double* b, int Lena, int Lenb){
    if(Lena != Lenb){
        cout << "Length a must euqals to Length b!";
        return 0;
    }
    else{
        double norm = 0;
        for(int i = 0; i < Lena; i ++){
            norm += (a[i] - b[i]) * (a[i] - b[i]);
        }
        norm = sqrt(norm);
        
        return norm;
    }
}

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
double spNormCol(SparseMatrix &Matrix){
    double sum = 0;
    double max = 0;
    
    // ||A||1 Maximum column vector sum
    for(int k = 0; k < Matrix.ColLength; k++){
        for(int j=0; j < Matrix.RowLength; j++){
            sum += abs(spGetElement(Matrix, j, k));
        }
        if(sum > max){
            max = sum;
        }
        sum = 0;
    }
    
    return max;
}

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
double spNormRow(SparseMatrix &Matrix){
    double sum = 0;
    double max = 0;
    
    // ||A||1 Maximum column vector sum
    for(int j = 0; j < Matrix.ColLength; j++){
        for(int k=0; k < Matrix.RowLength; k++){
            sum += abs(spGetElement(Matrix, j, k));
        }
        if(sum > max){
            max = sum;
        }
        sum = 0;
    }
    
    return max;
}

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
double spConditionNumber(SparseMatrix &Matrix, string NormType){
    double condition = 0;
    
    if(NormType == "NormCol"){
        SparseMatrix InverseDiagonal = spGetInverseDiagonal(Matrix);
        condition = spNormCol(Matrix) * spNormCol(InverseDiagonal);
    }
    
    else if(NormType == "NormRow"){
        SparseMatrix InverseDiagonal = spGetInverseDiagonal(Matrix);
        condition = spNormRow(Matrix) * spNormRow(InverseDiagonal);
    }
    
    else {
        cout << "Only 1-norm and inf-norm provided" << endl;
    }
    
    return condition;
}

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
SparseMatrix spGetDiagonal(SparseMatrix &Matrix){
    SparseMatrix Diagonal = spCreate(Matrix.RowLength, Matrix.ColLength, 0);
    
    for(int i = 0; i < Matrix.RowLength; i++){
        spAddElement(Diagonal, spGetElement(Matrix, i, i), i, i);
    }
    
    return Diagonal;
}

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
SparseMatrix spGetInverseDiagonal(SparseMatrix &Matrix){
    SparseMatrix InverseDiagonal = spCreate(Matrix.RowLength, Matrix.ColLength, Matrix.ColLength);
    
    for(int i = 0; i < Matrix.RowLength; i++){
        spAddElement(InverseDiagonal, 1.0 / spGetElement(Matrix, i, i), i, i);
    }
    
    return InverseDiagonal;
}


