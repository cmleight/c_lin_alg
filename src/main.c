
#ifndef _STD_LIB_INC_H_
#define _STD_LIB_INC_H_
    #include "stdlibinc.h"
#endif

#include "main.h"
#include "determinants.h"


int main( int argc, char* args[] )
{
    long double **matrix;

    int32_t i;

    size_t length = 4;
    size_t width  = 4;

    matrix = calloc(width, sizeof(long double*));

    for ( i = 0 ; i < width ; i++ )
    {
        matrix[i] = calloc(length, sizeof(long double));
    }

    // TODO: test sign determinism here

    for ( i = 0 ; i < width ; i++ )
    {
        free(matrix[i]);
    }
    free(matrix[i]);

    printf("starting version: %s\n", VERSION);
    return 0;
}

