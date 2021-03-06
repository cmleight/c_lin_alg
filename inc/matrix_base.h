/* inc/matrix_base.h.  Generated from matrix_base.h.in by configure.  */

#ifndef _STD_LIB_INC_H_
#define _STD_LIB_INC_H_
    #include "stdlibinc.h"
#endif


struct matrix {
    int64_t height;
    int64_t length;
    long double ** matrix;
};

#define SUCCESS          0
#define BASE_CALLOC_FAIL 1
#define ROW_CALLOC_FAIL  2
#define FREE_ROW_FAIL    3
#define FREE_BASE_FAIL   4


/*
 * Allocates memory for a matrix struct with the provided options
 */
int
alloc_matrix ( struct matrix** alloc, int64_t length, int64_t width );

/*
 * Re-allocates the matrix to the desired size
 */
int
resize_matrix ( struct matrix** alloc, int64_t height, int64_t length );

/*
 * Frees the matrix structure
 */
int
free_matrix ( struct matrix** alloc );

void
print_matrix ( struct matrix matrix );

