/* inc/determinants.h.  Generated from determinants.h.in by configure.  */

#ifndef _STD_LIB_INC_H_
#define _STD_LIB_INC_H_
    #include "stdlibinc.h"
    #include "matrix_base.h"
#endif

int
lu_decomp ( struct matrix* input_matrix, struct matrix* lower, struct matrix* upper );

/*
 * This will calculate the determinant of the matrix provided with given length and width.
 */
int
lu_determinant ( struct matrix* matrix, long double* result );

int
leplace_determinant ( struct matrix* matrix, long double* result);

/*
 * This will determine the sign for a row in the provided matrix when calculating determinant
 */
int64_t
row_inversions ( long double *column, int64_t length );

