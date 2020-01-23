

#ifndef _STDLIB_H_
#define _STDLIB_H_
    #include <stdint.h>
    #include <stddef.h>
#endif

void determinant ( long double **matrix, size_t length, size_t width )
{

}



/*
 * This will determine the sign for a row in the provided matrix when calculating determinant
 */
int8_t row_inversions ( long double *matrix, size_t length )
{
    size_t hits = 0;

    for ( int i = 0 ; i < length ; i++ )
    {
        for ( int j = i ; j < length ; j++ )
        {
            if ( matrix[i] > matrix[j] )
                ++hits;
        }
    }

    return hits;
}

