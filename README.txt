
Assignment 5: Sparse Matrix Solver
Author: Leslie Yu
Date: 05/18/2018
Platform: Xcode (Mac OS)
Description: The whole project is aimed to implement sparse matrix solver using direct solutions and iterative solutions with modules that have independent testing. Use the condition number to vericate the property of the matrix. Compare the performance of different solvers. Use top down design to implement the sparse matrix solver, which contains following part. The data structure is class SparseMatrix and pointer for ValPtr, RowPtr and ColPtr.

Files descriptions : 

1. spalloc.hpp and spalloc.cpp 
   
   This file contains the creation and memory allocations for sparse matrix.

2. spbuild.hpp and spbuild.cpp
   
   This file contains the routines associated with initialization, loading and processing the matrix for the sparse matrix routines.

3. spsolve.hpp and spsolve.cpp

   This file contains the direct solver and iterative solver for the sparse matrix.

4. sputils.hpp and sputils.cpp

   This file contains various optional utility routines.

5. spoutput.hpp and spoutput.cpp

   This file contains the output-to-file and output-toscreen routines for the matrix package.

6. spdefs.h

   This file contains data structure used for sparse matrix and macros for the sparse matrix routines. The definitions are of no use to the users.

7. spunittest.hpp and spunittest.cpp

   This file contains all tests for Sparse matrix. Unit testing, white box testing, black box testing, Wilkinson principle used.

8. memusage.hpp and memusage.cpp

   This file contains the memory monitor function.