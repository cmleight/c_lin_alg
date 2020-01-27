
#include "bench_time.h"

long double
time_diff ( struct bench_time* start, struct bench_time* end )
  {
    long double x_ms , y_ms , diff;
#if __STDC_VERSION__  < 201112L

    struct timeval x = start->time;
    struct timeval y = end->time;

    x_ms = ( (long double) x.tv_sec * 1000000 + (long double) x.tv_usec ) * 1000;
    y_ms = ( (long double) y.tv_sec * 1000000 + (long double) y.tv_usec ) * 1000;

#else

    // difference in nanoseconds

    struct timespec x = start->time;
    struct timespec y = end->time;

    x_ms = (long double) x.tv_sec * 1000000 * 1000 + (long double) x.tv_nsec;
    y_ms = (long double) y.tv_sec * 1000000 * 1000 + (long double) y.tv_nsec;


#endif
    diff = y_ms - x_ms;

    return diff;
  }

void
set_time ( struct bench_time* bench )
  {
#if __STDC_VERSION__  < 201112L
    gettimeofday ( &bench->time, 0 );
#else
    timespec_get ( &bench->time, TIME_UTC );
#endif
  }
