
#include "matrix_base.h"


#define DEBUG
#undef DEBUG
#define TRACE
#undef TRACE

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


int
alloc_matrix ( struct matrix** alloc, int64_t height, int64_t length )
  {
    if ( *alloc != 0 )
      {
        free_matrix ( alloc );
      }

    (*alloc) = calloc ( 1, sizeof ( struct matrix ) );
    if ( (*alloc) == 0 )
      {
        return BASE_CALLOC_FAIL;
      }
    (*alloc)->height = height;
    (*alloc)->length = length;
    (*alloc)->matrix = calloc ( height, sizeof ( long double * ) );
    for ( int i = 0 ; i < height ; i++ )
      {
        (*alloc)->matrix[i] = calloc ( length, sizeof ( long double ) );
        if ( (*alloc)->matrix[i] == 0 )
            return FREE_ROW_FAIL;
      }

    return SUCCESS;

  }

int
resize_matrix ( struct matrix** alloc, int64_t height, int64_t length )
  {
    int ret = SUCCESS;
    ret = free_matrix ( alloc );
    if ( ret != SUCCESS )
      {
         return ret;
      }
    ret = alloc_matrix ( alloc, height, length );
    return ret;
  }

int
free_matrix ( struct matrix** alloc )
  {
    if ( *alloc != 0 )
      {
        for ( int i = 0 ; i < (*alloc)->height ; i++ )
          {
            if ( (*alloc)->matrix[i] != 0 )
              {
                free ( (*alloc)->matrix[i] );
              }
          }
        free ( *alloc );
        *alloc = 0;
        return SUCCESS;
      }
    else
      {
        return SUCCESS;
      }
  }


void print_matrix ( struct matrix matrix )
{
    printf ( "{\n" );
    for (int i = 0 ; i < matrix.height ; i++ )
    {
        printf ( " {" );
        for (int j = 0 ; j < matrix.length ; j++ )
        {
            printf ( " %Lf ", matrix.matrix[i][j] );
        }
        printf ( "}\n" );
    }
    printf ( "}\n" );
}

