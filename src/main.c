
#include <assert.h>

#include "main.h"
#include "determinants.h"

#ifndef _STD_LIB_INC_H_
#define _STD_LIB_INC_H_
    #include "stdlibinc.h"
    #include "matrix_base.h"
#endif


#define DEBUG
#undef TRACE
#define TRACE

#ifdef DEBUG
    #define LOG_DEBUG printf
#else
    #define LOG_DEBUG(...)
#endif


#ifdef TRACE
    #define LOG_TRACE printf
#else
    #define LOG_TRACE(...)
#endif

void test_inversion ( int8_t  debug  );
void test_determinant ( int8_t  debug  );

int main( int argc, char *args[] )
{

    test_inversion ( 0 );
    test_determinant ( 1 );

    return 0;
}

void test_inversion ( int8_t  debug  )
{
    int64_t res;
    long double *test_matrix = calloc(4, sizeof(long double));

    LOG_DEBUG ( "Running tests for version: %s\n\n", VERSION );

    test_matrix[0] = 0;
    test_matrix[1] = 1;
    test_matrix[2] = 2;
    test_matrix[3] = 3;

    LOG_DEBUG ( "Testing inversions:\n" );

    res = row_inversions ( test_matrix , 4 );
    LOG_DEBUG ( "Expected : 0 Found : %ld\n", res );
    assert ( res == 0 );

    test_matrix[0] = 2;

    res = row_inversions ( test_matrix , 4 );
    LOG_DEBUG ( "Expected : 1 Found : %ld\n", res );
    assert ( res == 1 );

    test_matrix[0] = 3;

    res = row_inversions ( test_matrix , 4 );
    LOG_DEBUG ( "Expected : 2 Found : %ld\n", res );
    assert ( res == 2 );

    test_matrix[0] = 4;
    test_matrix[1] = 3;
    test_matrix[2] = 1;
    test_matrix[3] = 2;

    res = row_inversions ( test_matrix , 4 );
    LOG_DEBUG ( "Expected : 5 Found : %ld\n", res );
    assert ( res == 5 );

    LOG_DEBUG ("\n" );

    free ( test_matrix );
}

void
assign_array ( long double **ptr, long double input[], size_t height, size_t row )
{
    for ( int i = 0 ; i < height ; i++ )
    {
        LOG_TRACE ( "Assigning %Lf to %p in %d\n", input[i], (void *) ptr[row], i );
        ptr[row][i] = input[i];
    }
}

void
test_determinant ( int8_t debug  )
{
    int res = 0;
    struct matrix* test_matrix = 0;
    long double array_1   [6] = { 1, 2, 3, 4, 5, 6 };
    long double array_2_1 [2] = { 3, 8 };
    long double array_2_2 [2] = { 4, 6 };
    long double array_2_1_2 [2] = { 3, 1 };
    long double array_2_2_2 [2] = { 4, 2 };
    long double array_3_1 [3] = { 6,  1, 1 };
    long double array_3_2 [3] = { 4, -2, 5 };
    long double array_3_3 [3] = { 2,  8, 7 };
    long double* result = calloc (1, sizeof ( long double ) );

    LOG_DEBUG ("Testing Determinant:\n" );

    alloc_matrix ( &test_matrix, 6, 6 );

    assign_array ( test_matrix->matrix, array_1, test_matrix->length, 0 );
    assign_array ( test_matrix->matrix, array_1, test_matrix->length, 1 );
    assign_array ( test_matrix->matrix, array_1, test_matrix->length, 2 );
    assign_array ( test_matrix->matrix, array_1, test_matrix->length, 3 );
    assign_array ( test_matrix->matrix, array_1, test_matrix->length, 4 );
    assign_array ( test_matrix->matrix, array_1, test_matrix->length, 5 );

#ifdef TRACE
    print_matrix ( *test_matrix );
#endif

    res = lu_determinant ( test_matrix, result );
    LOG_DEBUG ( "Result 1: %Lf\n", *result );
    assert ( *result == 0 );

    alloc_matrix ( &test_matrix, 2, 2 );

    assign_array ( test_matrix->matrix, array_2_1_2, test_matrix->length, 0 );
    assign_array ( test_matrix->matrix, array_2_2_2, test_matrix->length, 1 );

#ifdef TRACE
    print_matrix ( *test_matrix );
#endif

    res = lu_determinant ( test_matrix, result );
    LOG_DEBUG ( "Result 2: %Lf\n", *result );
    assert ( *result == 2);

    alloc_matrix ( &test_matrix, 2, 2 );

    assign_array ( test_matrix->matrix, array_2_1, test_matrix->length, 0 );
    assign_array ( test_matrix->matrix, array_2_2, test_matrix->length, 1 );

#ifdef TRACE
    print_matrix ( *test_matrix );
#endif

    res = lu_determinant ( test_matrix, result );
    LOG_DEBUG ( "Result 2: %Lf\n", *result );
    assert ( *result == -14 );


    alloc_matrix ( &test_matrix, 3, 3 );

    assign_array ( test_matrix->matrix, array_3_1, test_matrix->length, 0 );
    assign_array ( test_matrix->matrix, array_3_2, test_matrix->length, 1 );
    assign_array ( test_matrix->matrix, array_3_3, test_matrix->length, 2 );

#ifdef TRACE
    print_matrix ( *test_matrix );
#endif

    res = lu_determinant ( test_matrix, result );
    LOG_DEBUG ( "Result 2: %Lf\n", *result );
    assert ( *result == -306 );
    free_matrix ( &test_matrix );


}

