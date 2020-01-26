

#ifndef _STD_LIB_INC_H_
#define _STD_LIB_INC_H_
    #include "stdlibinc.h"
    #include "matrix_base.h"
#endif


// #undef DEBUG
#define DEBUG
#ifdef DEBUG
    #define LOG_DEBUG printf
#else
    #define LOG_DEBUG(...)
#endif

int64_t
modulo_Euclidean(int64_t a, int64_t b)
  {
    int64_t m = a % b;
    if (m < 0)
      {
        m = (b < 0) ? m - b : m + b;
      }
    return m;
  }

int
lu_decomp ( struct matrix* input_matrix, struct matrix** lower, struct matrix** upper )
  {
    int i = 0;
    int j = 0;
    int k = 0;
    long double** lower_matrix;
    long double** upper_matrix;
    long double** base_matrix;

    int64_t height = input_matrix->height;
    int64_t length = input_matrix->length;

    alloc_matrix ( lower, height, length );
    alloc_matrix ( upper, height, length );

    lower_matrix = (*lower)->matrix;
    upper_matrix = (*upper)->matrix;
    base_matrix = input_matrix->matrix;

    // setup the upper and lower triangle matricies.
    for ( i = 0 ; i < length ; i++ )
      {
        upper_matrix[0][i] = base_matrix[0][i];
        lower_matrix[i][i] = 1;
      }

    // Gaussian Elimination to get the upper and lower triangles.
    for ( j = 0 ; j < length - 1 ; j++ )
      {
        if ( upper_matrix[j][j] == 0 )
          {
            free_matrix ( lower );
            free_matrix ( upper );
            return -1;
          }
        else
          {
            for ( i = j + 1 ; i < height ; i++ )
              {
                if ( j == 0 )
                  {
	            lower_matrix[i][j] = base_matrix[i][j] / base_matrix[j][j];
                  }
                else
                  {
                    lower_matrix[i][j] = upper_matrix[i][j] / upper_matrix[j][j];
                  }
                for ( k = length - 1 ; k >= i - 1 ; k-- )
                  {
                    if ( j == 0 )
                      {
                        upper_matrix[i][k] = base_matrix[i][k] - base_matrix[j][k] * ( base_matrix[i][j] / base_matrix[j][j] );
                      }
                    else
                      {
                        upper_matrix[i][k] = upper_matrix[i][k] - upper_matrix[j][k] * ( upper_matrix[i][j] / upper_matrix[j][j] );
                      }
                    #ifdef DEBUG
                    printf ( "Lower:\n" );
                    print_matrix ( **lower );
                    printf ( "Upper:\n" );
                    print_matrix ( **upper );
                    #endif
                  }
              }
          }
      }

    return 0;
  }

int
lu_determinant ( struct matrix* input_matrix, long double* result )
  {
    int64_t i;
    struct matrix* lower = 0;
    struct matrix* upper = 0;
    int res = 0;

    *result = 1;

    res = lu_decomp ( input_matrix, &lower, &upper );

    if ( res == -1 )
      {
        *result = 0;
        return 0;
      }

    for ( i = 0 ; i < input_matrix->height ; i++ )
      {
        *result = *result * lower->matrix[i][i] * upper->matrix[i][i];
      }

    free_matrix ( &lower );
    free_matrix ( &upper );

    return res;
  }


// TODO: actually implement the recursive formula or this.
int
leplace_determinant ( struct matrix* input_matrix, long double* result )
  {
    long double det = 0;
    long double add_mult;
    long double sub_mult;

    for ( int i = 0 ; i < input_matrix->height ; i += 2 )
      {
        add_mult = 1;
        sub_mult = 1;
        for ( int j = 0 ; j <  input_matrix->length ; j++ )
          {
            add_mult = add_mult * input_matrix->matrix[ modulo_Euclidean ( i + j, input_matrix->height )][j];
            if ( i + 1 < input_matrix->height )
                sub_mult = sub_mult * input_matrix->matrix[ modulo_Euclidean ( i + 1  - j, input_matrix->height )][j];
            else
                sub_mult = 0;
            LOG_DEBUG ( "Location: (%d, %d) : values add: %Lf subtract: %Lf\n", i, j, add_mult, sub_mult );
          }
        det = det + add_mult - sub_mult;
        LOG_DEBUG ( "Post update det: %Lf\n", det );
      }
    return 0;
  }



/*
 * This will determine the sign for a row in the provided matrix when calculating determinant
 */
int64_t row_inversions ( long double* matrix, int64_t length )
{
    int64_t hits = 0;

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

